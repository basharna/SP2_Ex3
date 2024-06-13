#include "Player.hpp"
#include "Catan.hpp"
#include <iostream>

using namespace std;

int main()
{
    Player player1("Player 1");
    Player player2("Player 2");
    Player player3("Player 3");

    Catan catan = Catan::getInstance(&player1, &player2, &player3);
    catan.chooseStartingPlayer();

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

    player1.rollDice();
    player1.buyDevelopmentCard();
    player1.endTurn();

    player2.rollDice();
    player2.buyDevelopmentCard();
    player2.endTurn();

    player3.rollDice();
    player3.buyDevelopmentCard();
    player3.endTurn();

    player1.rollDice();
    player1.useMonopolyCard();
    player1.endTurn();

    player2.rollDice();
    player2.trade(&player1, Resource::BRICK, Resource::ORE, 1);
    player2.endTurn();

    player1.printPlayerStats();
    player2.printPlayerStats();
    player3.printPlayerStats();

    return 0;
}