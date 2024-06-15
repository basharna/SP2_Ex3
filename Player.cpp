#include "Player.hpp"
#include "Board.hpp"
#include "Catan.hpp"

mt19937 Player::rng(chrono::system_clock::now().time_since_epoch().count());

Player::Player(string name)
    : name(name),
      board(nullptr),
      game(nullptr),
      victoryPoints(0),
      playerID(-1),
      turn(false),
      hasRolled(false)
{
    this->resources[Resource::WOOD] = 0;
    this->resources[Resource::BRICK] = 0;
    this->resources[Resource::WOOL] = 0;
    this->resources[Resource::WHEAT] = 0;
    this->resources[Resource::ORE] = 0;

    for (int i = 0; i < 3; i++)
    {
        this->unbuiltSettlements.insert(new Building(BuildingType::SETTLEMENT, this));
    }

    for (int i = 0; i < 4; i++)
    {
        this->unbuiltCities.insert(new Building(BuildingType::CITY, this));
    }

    for (int i = 0; i < 13; i++)
    {
        this->unbuiltRoads.insert(new Building(BuildingType::ROAD, this));
    }

    for (int i = 0; i < 2; i++)
    {
        this->startingSettlements.insert(new Building(BuildingType::STARTING_SETTLEMENT, this));
        this->startingRoads.insert(new Building(BuildingType::STARTING_ROAD, this));
    }
}

Player::~Player()
{
    for (auto building : unbuiltSettlements)
    {
        delete building;
    }
    unbuiltSettlements.clear();

    for (auto building : unbuiltCities)
    {
        delete building;
    }
    unbuiltCities.clear();

    for (auto building : unbuiltRoads)
    {
        delete building;
    }
    unbuiltRoads.clear();

    for (auto building : startingSettlements)
    {
        delete building;
    }
    startingSettlements.clear();

    for (auto building : startingRoads)
    {
        delete building;
    }
    startingRoads.clear();
}

void Player::setPlayerID(int id)
{
    this->playerID = id;
}

void Player::setTurn(bool turn)
{
    this->turn = turn;
}

void Player::setBoard(Board *board)
{
    this->board = board;
}

void Player::setGame(Catan *game)
{
    this->game = game;
}

string Player::getName()
{
    return this->name;
}

int Player::getPlayerID()
{
    return this->playerID;
}

int Player::getVictoryPoints()
{
    return this->victoryPoints;
}

int Player::getResourceCount(Resource resource)
{
    return this->resources[resource];
}

unordered_set<Building *> Player::getBuildings()
{
    return this->buildings;
}

Building *Player::getUnbuiltSettlement()
{
    Building *building = nullptr;
    if (this->startingSettlements.size() > 0)
    {
        // pop the first element from the set
        building = *this->startingSettlements.begin();
        this->startingSettlements.erase(building);
    }
    else if (this->unbuiltSettlements.size() > 0)
    {
        // pop the first element from the set
        building = *this->unbuiltSettlements.begin();
        if (!canAfford(building->getCost()))
        {
            cout << "Cannot afford settlement" << endl;
            return nullptr;
        }
        this->unbuiltSettlements.erase(building);
    }

    return building;
}

Building *Player::getUnbuiltRoad()
{
    Building *building = nullptr;

    if (this->startingRoads.size() > 0)
    {
        // pop the first element from the set
        building = *this->startingRoads.begin();
        this->startingRoads.erase(building);
    }
    else if (this->unbuiltRoads.size() > 0)
    {
        // pop the first element from the set
        building = *this->unbuiltRoads.begin();
        if (!canAfford(building->getCost()))
        {
            cout << "player cant afford Road" << endl;
            return nullptr;
        }
        this->unbuiltRoads.erase(building);
    }

    return building;
}

Building *Player::getUnbuiltCity()
{
    // pop the first element from the set
    Building *building = *this->unbuiltCities.begin();
    this->unbuiltCities.erase(building);

    return building;
}

int Player::getUnbuiltStartingSettlementsCount()
{
    return this->startingSettlements.size();
}

int Player::getUnbuiltStartingRoadsCount()
{
    return this->startingRoads.size();
}

void Player::addResource(Resource resource, int amount)
{
    this->resources[resource] += amount;
}

void Player::removeResource(Resource resource, int amount)
{
    this->resources[resource] -= amount;
}

bool Player::placeRoad(int vertexID1, int vertexID2)
{
    // check if player's turn
    if (this->getUnbuiltStartingRoadsCount() == 0)
    {
        if (!this->turn)
        {
            cout << "Not player's turn" << endl;
            return false;
        }
        if (!this->hasRolled)
        {
            cout << "Player must roll dice before placing road" << endl;
            return false;
        }
    }

    Building *road = getUnbuiltRoad();
    if (road == nullptr)
    {
        cout << "Cannot build road: " << vertexID1 << "," << vertexID2 << endl;
        return false;
    }
    road->setVertexIds({vertexID1, vertexID2});

    // check if player can build road on board
    if (!board->buildRoad(road))
    {
        cout << "Cannot build road: " << vertexID1 << "," << vertexID2 << endl;
        return false;
    }
    road->setBuilt(true);
    deductCost(road->getCost());
    this->buildings.insert(road);

    return true;
}

bool Player::placeSettlement(int vertexID)
{
    if (this->getUnbuiltStartingSettlementsCount() == 0)
    {
        if (!this->turn)
        {
            cout << "Not player's turn" << endl;
            return false;
        }
        if (!this->hasRolled)
        {
            cout << "Player must roll dice before placing settlement" << endl;
            return false;
        }
    }

    Building *settlement = getUnbuiltSettlement();
    if (settlement == nullptr)
    {
        return false;
    }
    settlement->setVertexIds({vertexID});

    // check if player can build settlement on board
    if (!board->buildSettlement(settlement))
    {
        cout << "Cannot build settlement: " << vertexID << endl;
        return false;
    }
    settlement->setBuilt(true);
    deductCost(settlement->getCost());
    addVictoryPoints(1);
    this->buildings.insert(settlement);

    Vertex *v = board->getVertex(vertexID);
    // if is starting settlement give resources to the player
    if (settlement->isStartingBuilding())
    {
        for (auto *tile : v->getTiles())
        {
            this->addResource(tile->getResource(), 1);
        }
    }
    return true;
}

bool Player::placeCity(int vertexID)
{
    // check if player's turn
    if (!this->turn)
    {
        cout << "Not player's turn" << endl;
        return false;
    }

    if (!this->hasRolled)
    {
        cout << "Player must roll dice before placing city" << endl;
        return false;
    }

    Building *city = getUnbuiltCity();
    if (city == nullptr)
    {
        cout << "Cannot build city" << endl;
        return false;
    }
    city->setVertexIds({vertexID});

    // check if player can build city on board
    if (!board->buildCity(city))
    {
        cout << "Cannot build city" << endl;
        return false;
    }
    city->setBuilt(true);
    deductCost(city->getCost());
    addVictoryPoints(1);
    this->buildings.insert(city);

    // remove settlement at the same vertex from buildings
    for (auto it = buildings.begin(); it != buildings.end(); ++it)
    {
        if ((*it)->getType() == BuildingType::SETTLEMENT && (*it)->getVertexIds() == city->getVertexIds())
        {
            buildings.erase(it);
            break;
        }
    }
    return true;
}

bool Player::endTurn()
{
    if (!this->turn)
    {
        return false;
    }
    this->turn = false;
    this->hasRolled = false;
    this->game->updateTurn(this);

    return true;
}

int Player::rollDice()
{
    // check if it is the player's turn
    if (!this->turn)
    {
        cout << "Not player's turn" << endl;
        return -1;
    }

    this->hasRolled = true;

    // Roll two dice
    uniform_int_distribution<> dist(1, 6);
    int sum = dist(rng) + dist(rng);

    cout << "Player " << this->name << " rolled " << sum << endl;

    if (sum == 7)
    {
        for (auto &p : this->game->getPlayers())
        {
            p->discardResources();
        }
    }
    else
    {
        collectResources(sum);
    }
    return sum;
}

bool Player::trade(Player *player, Resource give, int give_amount, Resource receive, int recv_amount)
{
    if (!this->turn)
    {
        cout << "Not player's turn" << endl;
        return false;
    }

    if (this->getResourceCount(give) < give_amount)
    {
        cout << "Not enough resources to trade" << endl;
        return false;
    }

    if (player->getResourceCount(receive) < recv_amount)
    {
        cout << "Player does not have enough resources to trade" << endl;
        return false;
    }

    this->removeResource(give, give_amount);
    this->addResource(receive, recv_amount);

    player->removeResource(receive, recv_amount);
    player->addResource(give, give_amount);

    cout << this->name << " traded " << give_amount << " " << to_string(give) << " for " << recv_amount << " " << to_string(receive) << " with " << player->getName() << endl;
    return true;
}

void Player::addVictoryPoints(int amount)
{
    victoryPoints += amount;
}

void Player::removeVictoryPoints(int amount)
{
    victoryPoints -= amount;
}

bool Player::canAfford(BuildingCost cost)
{
    return resources[Resource::WOOD] >= cost.wood &&
           resources[Resource::BRICK] >= cost.brick &&
           resources[Resource::WOOL] >= cost.wool &&
           resources[Resource::WHEAT] >= cost.wheat &&
           resources[Resource::ORE] >= cost.ore;
}

void Player::deductCost(BuildingCost cost)
{
    removeResource(Resource::WOOD, cost.wood);
    removeResource(Resource::BRICK, cost.brick);
    removeResource(Resource::WOOL, cost.wool);
    removeResource(Resource::WHEAT, cost.wheat);
    removeResource(Resource::ORE, cost.ore);
}

void Player::collectResources(int diceRoll)
{
    for (int i = 0; i <= 18; i++)
    {
        Tile *tile = this->board->getTile(i);
        if (tile == nullptr)
        {
            cout << "Tile not found" << endl;
            exit(1);
        }
        if (tile->getToken() == diceRoll)
        {
            for (auto &v : tile->getVertices())
            {
                if (v->hasBuilding())
                {
                    Building *building = v->getBuilding();
                    if (building->getType() == BuildingType::SETTLEMENT || building->getType() == BuildingType::STARTING_SETTLEMENT)
                    {
                        building->getOwner()->addResource(tile->getResource(), 1);
                    }
                    else if (building->getType() == BuildingType::CITY)
                    {
                        building->getOwner()->addResource(tile->getResource(), 2);
                    }
                }
            }
        }
    }
}

void Player::discardResources()
{
    int totalResources = 0;
    for (auto &r : this->resources)
    {
        totalResources += r.second;
    }
    if (totalResources > 7)
    {
        int discardCount = totalResources / 2;
        cout << "Player " << this->name << " must discard " << discardCount << " resources" << endl;

        // discard half of each resource
        for (auto &r : this->resources)
        {
            int discardAmount = r.second / 2;
            this->resources[r.first] -= discardAmount;
            discardCount -= discardAmount;
            if (discardCount == 0)
            {
                break;
            }
        }
    }
}

void Player::printPlayerStats()
{
    cout << "-------------------------------" << endl;
    cout << "Player: " << this->name << endl;
    cout << "   Victory Points: " << this->victoryPoints << endl;
    cout << "   Resources: " << endl;
    cout << "       Wood: " << this->resources[Resource::WOOD] << endl;
    cout << "       Brick: " << this->resources[Resource::BRICK] << endl;
    cout << "       Wool: " << this->resources[Resource::WOOL] << endl;
    cout << "       Wheat: " << this->resources[Resource::WHEAT] << endl;
    cout << "       Ore: " << this->resources[Resource::ORE] << endl;
    cout << "   Buildings: ";
    for (auto &b : this->buildings)
    {
        cout << b->getTypeString() << " " << b->getPositionString() << " | ";
    }
    cout << endl;
    cout << "   Cards:";
    for (auto &c : this->developmentCards)
    {
        cout << " " << CardDeck::cardToString(c) << " |";
    }
    cout << endl;
}

void Player::buyDevelopmentCard()
{
    if (!this->turn)
    {
        cout << "Not player's turn" << endl;
        return;
    }

    if (!canAfford({0, 0, 1, 1, 1}))
    {
        cout << "Cannot afford development card" << endl;
        return;
    }

    Card card = this->game->getCardDeck().drawCard();
    if (card == Card::EMPTY)
    {
        cout << "No cards left in deck" << endl;
        return;
    }

    this->developmentCards.insert(Card(card));
    deductCost({0, 0, 1, 1, 1});

    // check how many knights the player has, if 3, give 2 victory points
    if (card == Card::KNIGHT)
    {
        int knightCount = 0;
        for (auto &c : this->developmentCards)
        {
            if (c == Card::KNIGHT)
            {
                knightCount++;
            }
        }
        if (knightCount == 3)
        {
            addVictoryPoints(2);
        }
    }
}

bool Player::useMonopolyCard(Resource resource)
{
    if (!this->turn)
    {
        cout << "Not player's turn" << endl;
        return false;
    }

    if (this->developmentCards.find(Card(Card::MONOPOLY)) == this->developmentCards.end())
    {
        cout << "Player does not have monopoly card" << endl;
        return false;
    }

    for (auto &p : this->game->getPlayers())
    {
        if (p == this)
        {
            continue;
        }
        int amount = p->getResourceCount(resource);
        cout << p->getName() << " had " << amount << " " << to_string(resource) << endl;
        p->removeResource(resource, amount);
        this->addResource(resource, amount);
    }

    // remove used card
    this->developmentCards.erase(Card(Card::MONOPOLY));
    cout << this->getName() << " used a Monopoly card" << endl;
    return true;
}

void Player::useYearOfPlentyCard()
{
    if (!this->turn)
    {
        cout << "Not player's turn" << endl;
        return;
    }

    if (this->developmentCards.find(Card(Card::YEAR_OF_PLENTY)) == this->developmentCards.end())
    {
        cout << "Player does not have year of plenty card" << endl;
        return;
    }

    cout << "Choose two resources to take" << endl;
    cout << "1. Wood" << endl;
    cout << "2. Brick" << endl;
    cout << "3. Wool" << endl;
    cout << "4. Wheat" << endl;
    cout << "5. Ore" << endl;

    int choice1, choice2;
    cin >> choice1 >> choice2;

    Resource resource1, resource2;
    switch (choice1)
    {
    case 1:
        resource1 = Resource::WOOD;
        break;
    case 2:
        resource1 = Resource::BRICK;
        break;
    case 3:
        resource1 = Resource::WOOL;
        break;
    case 4:
        resource1 = Resource::WHEAT;
        break;
    case 5:
        resource1 = Resource::ORE;
        break;
    default:
        cout << "Invalid choice" << endl;
        return;
    }

    switch (choice2)
    {
    case 1:
        resource2 = Resource::WOOD;
        break;
    case 2:
        resource2 = Resource::BRICK;
        break;
    case 3:
        resource2 = Resource::WOOL;
        break;
    case 4:
        resource2 = Resource::WHEAT;
        break;
    case 5:
        resource2 = Resource::ORE;
        break;
    default:
        cout << "Invalid choice" << endl;
        return;
    }

    this->addResource(resource1, 1);
    this->addResource(resource2, 1);

    // remove used card
    this->developmentCards.erase(Card(Card::YEAR_OF_PLENTY));
}

void Player::useRoadBuildingCard()
{
    if (!this->turn)
    {
        cout << "Not player's turn" << endl;
        return;
    }

    if (this->developmentCards.find(Card(Card::ROAD_BUILDING)) == this->developmentCards.end())
    {
        cout << "Player does not have road building card" << endl;
        return;
    }

    cout << "Place two roads" << endl;
    cout << "Enter the vertex IDs of the two ends of the first road" << endl;

    int vertexID1, vertexID2;
    cin >> vertexID1 >> vertexID2;

    while (!placeRoad(vertexID1, vertexID2))
    {
        cout << "invalid road, enter again" << endl;
        cin >> vertexID1 >> vertexID2;
    }

    cout << "Enter the vertex IDs of the two ends of the second road" << endl;
    cin >> vertexID1 >> vertexID2;

    while (!placeRoad(vertexID1, vertexID2))
    {
        cout << "invalid road, enter again" << endl;
        cin >> vertexID1 >> vertexID2;
    }

    // remove used card
    this->developmentCards.erase(Card(Card::ROAD_BUILDING));
}

void Player::useVictoryPointCard()
{
    if (!this->turn)
    {
        cout << "Not player's turn" << endl;
        return;
    }

    if (this->developmentCards.find(Card(Card::VICTORY_POINT)) == this->developmentCards.end())
    {
        cout << "Player does not have victory point card" << endl;
        return;
    }

    addVictoryPoints(1);
}

void Player::addDevelopmentCard(Card card)
{
    this->developmentCards.insert(card);
}

void Player::setHasRolled(bool hasRolled)
{
    this->hasRolled = hasRolled;
}
