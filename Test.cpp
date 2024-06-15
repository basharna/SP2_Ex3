#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Catan.hpp"

// test placing initial settlements
TEST_CASE("Test placing initial settlements")
{
    Player player1("Player 1");
    Player player2("Player 2");
    Player player3("Player 3");

    Catan catan = Catan(&player1, &player2, &player3);
    catan.chooseStartingPlayer();

    SUBCASE("Test placing initial settlements correctly")
    {
        cout << "-------------TEST PLACING INITIAL SETTLEMENTS CORRECTLY-------------" << endl;
        CHECK(player1.placeRoad(19, 9) == true);
        CHECK(player1.placeSettlement(9) == true);
        CHECK(player2.placeRoad(1, 2) == true);
        CHECK(player2.placeSettlement(2) == true);
        CHECK(player3.placeRoad(45, 53) == true);
        CHECK(player3.placeSettlement(53) == true);
    }

    SUBCASE("Test placing initial settlements incorrectly")
    {
        cout << "-------------TEST PLACING INITIAL SETTLEMENTS INCORRECTLY-------------" << endl;
        CHECK(player1.placeSettlement(38) == false);
        CHECK(player2.placeSettlement(26) == false);
        CHECK(player3.placeSettlement(16) == false);
    }
}

TEST_CASE("Test placing all 6 starting buildings and then placing building without rollDice")
{
    cout << "-------------TEST PLACING ALL 6 STARTING BUILDINGS AND THEN PLACING BUILDING WITHOUT ROLL DICE-------------" << endl;
    Player player1("Player 1");
    Player player2("Player 2");
    Player player3("Player 3");

    Catan catan = Catan(&player1, &player2, &player3);
    catan.setStartingPlayer(1);

    CHECK(player1.placeRoad(19, 9) == true);
    CHECK(player1.placeSettlement(9) == true);

    CHECK(player2.placeRoad(1, 2) == true);
    CHECK(player2.placeSettlement(2) == true);

    CHECK(player3.placeRoad(45, 53) == true);
    CHECK(player3.placeSettlement(53) == true);

    CHECK(player1.placeRoad(21, 11) == true);
    CHECK(player1.placeSettlement(11) == true);

    CHECK(player2.placeRoad(47, 48) == true);
    CHECK(player2.placeSettlement(48) == true);

    CHECK(player3.placeRoad(27, 16) == true);
    CHECK(player3.placeSettlement(16) == true);

    CHECK(player1.placeRoad(51, 52) == false);

    CHECK(player1.rollDice() != -1);
    player1.addResource(Resource::WOOD, 1);
    player1.addResource(Resource::BRICK, 1);
    CHECK(player1.placeRoad(11, 12) == true);
    CHECK(player1.placeSettlement(12) == false);
}

TEST_CASE("Test buildings posiotion")
{
    cout << "-------------TEST BUILDINGS POSITION-------------" << endl;
    Player player1("Player 1");
    Player player2("Player 2");
    Player player3("Player 3");

    Catan catan = Catan(&player1, &player2, &player3);
    catan.setStartingPlayer(1);

    CHECK(player1.placeRoad(19, 9) == true);
    CHECK(player1.placeSettlement(9) == true);

    // get the position of the settlement, it should be 9
    unordered_set<Building *> buildings = player1.getBuildings();
    for (Building *building : buildings)
    {
        if (building->getType() == BuildingType::SETTLEMENT)
        {
            CHECK(building->getVertexIds().at(0) == 9);
        }
        if (building->getType() == BuildingType::ROAD)
        {
            CHECK(building->getVertexIds().at(0) == 19);
            CHECK(building->getVertexIds().at(1) == 9);
        }
    }
}

TEST_CASE("Test initial resource distribution")
{
    cout << "-------------TEST INITIAL RESOURCE DISTRIBUTION-------------" << endl;
    Player player1("Player 1");
    Player player2("Player 2");
    Player player3("Player 3");

    Catan catan = Catan(&player1, &player2, &player3);
    catan.chooseStartingPlayer();

    CHECK(player1.placeRoad(19, 9) == true);
    CHECK(player1.placeSettlement(9) == true);

    CHECK(player1.getResourceCount(Resource::ORE) == 1);
    CHECK(player1.getResourceCount(Resource::BRICK) == 1);
    CHECK(player1.getResourceCount(Resource::WHEAT) == 1);
}

TEST_CASE("Test resource allocation after dice roll")
{
    cout << "-------------TEST RESOURCE ALLOCATION AFTER DICE ROLL-------------" << endl;
    Player player1("Player 1");
    Player player2("Player 2");
    Player player3("Player 3");

    Catan catan = Catan(&player1, &player2, &player3);
    catan.setStartingPlayer(1);

    // Place settlements on tiles with number 6 and simulate a roll of 6
    CHECK(player1.placeRoad(19, 9) == true);
    CHECK(player1.placeSettlement(9) == true);

    catan.simulateDiceRoll(&player1, 6);

    CHECK(player1.getResourceCount(Resource::BRICK) == 2);
}

TEST_CASE("Test placing roads adjacent to settlements")
{
    cout << "-------------TEST PLACING ROADS ADJACENT TO SETTLEMENTS-------------" << endl;
    Player player1("Player 1");
    Player player2("Player 2");
    Player player3("Player 3");

    Catan catan = Catan(&player1, &player2, &player3);
    catan.setStartingPlayer(1);

    // place initial settlements and roads
    player1.placeRoad(19, 9);
    player1.placeSettlement(9);

    player2.placeRoad(1, 2);
    player2.placeSettlement(2);

    player3.placeRoad(45, 53);
    player3.placeSettlement(53);

    player1.placeRoad(21, 11);
    player1.placeSettlement(11);

    player2.placeRoad(47, 48);
    player2.placeSettlement(48);

    player3.placeRoad(27, 16);
    player3.placeSettlement(16);

    // give player1 resources to build a road
    player1.addResource(Resource::BRICK, 10);
    player1.addResource(Resource::WOOD, 10);

    cout << *catan.getBoard() << endl;

    catan.simulateDiceRoll(&player1, 6);
    CHECK(player1.placeRoad(30, 31) == false);

    CHECK(player1.placeRoad(9, 8) == true);
}

TEST_CASE("Test trading between players")
{
    cout << "-------------TEST TRADING BETWEEN PLAYERS-------------" << endl;
    Player player1("Player 1");
    Player player2("Player 2");
    Player player3("Player 3");

    Catan catan = Catan(&player1, &player2, &player3);
    catan.chooseStartingPlayer();
    catan.setStartingPlayer(1);

    player1.addResource(Resource::WOOD, 2);
    player2.addResource(Resource::BRICK, 2);

    // Trade 1 wood for 1 brick
    CHECK(player1.trade(&player2, Resource::WOOD, 1, Resource::BRICK, 1) == true);
    CHECK(player1.getResourceCount(Resource::WOOD) == 1);
    CHECK(player1.getResourceCount(Resource::BRICK) == 1);
    CHECK(player2.getResourceCount(Resource::WOOD) == 1);
    CHECK(player2.getResourceCount(Resource::BRICK) == 1);
}

TEST_CASE("Test development card usage")
{
    cout << "-------------TEST DEVELOPMENT CARD USAGE-------------" << endl;
    Player player1("Player 1");
    Player player2("Player 2");
    Player player3("Player 3");

    Catan catan = Catan(&player1, &player2, &player3);
    catan.setStartingPlayer(1);

    player1.addResource(Resource::ORE, 1);
    player1.addResource(Resource::WHEAT, 1);
    player1.addResource(Resource::WOOL, 1);

    player2.addResource(Resource::ORE, 1);
    player3.addResource(Resource::ORE, 1);
    CHECK(player2.getResourceCount(Resource::ORE) == 1);
    CHECK(player3.getResourceCount(Resource::ORE) == 1);

    player1.buyDevelopmentCard();
    CHECK(player1.getResourceCount(Resource::ORE) == 0);
    CHECK(player1.getResourceCount(Resource::WHEAT) == 0);
    CHECK(player1.getResourceCount(Resource::WOOL) == 0);

    Card monopoly = Card::MONOPOLY;
    player1.addDevelopmentCard(monopoly);

    CHECK(player1.useMonopolyCard(Resource::ORE) == true);
    CHECK(player1.getResourceCount(Resource::ORE) == 2);
    CHECK(player2.getResourceCount(Resource::ORE) == 0);
    CHECK(player3.getResourceCount(Resource::ORE) == 0);
}

TEST_CASE("Test building placement edge cases")
{
    cout << "-------------TEST BUILDING PLACEMENT EDGE CASES-------------" << endl;
    Player player1("Player 1");
    Player player2("Player 2");
    Player player3("Player 3");

    Catan catan = Catan(&player1, &player2, &player3);
    catan.chooseStartingPlayer();
    catan.setStartingPlayer(1);

    // Place initial settlements and roads
    CHECK(player1.placeRoad(19, 9) == true);
    CHECK(player1.placeSettlement(9) == true);

    CHECK(player2.placeRoad(0, 8) == true);
    CHECK(player2.placeSettlement(8) == false);

    CHECK(player3.placeRoad(9, 10) == true);
    CHECK(player3.placeSettlement(9) == false);
}

TEST_CASE("Test turn updating")
{
    cout << "-------------TEST TURN UPDATING-------------" << endl;
    Player player1("Player 1");
    Player player2("Player 2");
    Player player3("Player 3");

    Catan catan = Catan(&player1, &player2, &player3);
    catan.setStartingPlayer(1);

    player1.placeRoad(19, 9);
    player1.placeSettlement(9);

    player2.placeRoad(1, 2);
    player2.placeSettlement(2);

    player3.placeRoad(45, 53);
    player3.placeSettlement(53);

    player1.placeRoad(21, 11);
    player1.placeSettlement(11);

    player2.placeRoad(47, 48);
    player2.placeSettlement(48);

    player3.placeRoad(27, 16);
    player3.placeSettlement(16);

    CHECK(player1.rollDice() != -1);
    CHECK(player1.endTurn() == true);

    CHECK(player2.rollDice() != -1);
    CHECK(player2.endTurn() == true);

    CHECK(player3.rollDice() != -1);
    CHECK(player3.endTurn() == true);
}


