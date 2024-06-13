#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <random>
#include "Resources.hpp"
#include "Building.hpp"
#include "Vertex.hpp"
#include "CardDeck.hpp"

using namespace std;
class Board;
class Catan;
class Player
{
public:
    Player(string name);

    // Getters
    string getName();
    int getPlayerID();
    int getVictoryPoints();
    int getResourceCount(Resource resource);
    unordered_set<Building *> getBuildings();
    Building *getUnbuiltSettlement();
    Building *getUnbuiltRoad();
    Building *getUnbuiltCity();
    int getUnbuiltStartingSettlementsCount();
    int getUnbuiltStartingRoadsCount();

    // Setters
    void setPlayerID(int id);
    void setTurn(bool turn);
    void setBoard(Board *board);
    void setGame(Catan *game);

    // Building
    bool placeSettlement(int vertexID);
    bool placeRoad(int vertexID1, int vertexID2);
    bool placeCity(int vertexID);

    // Game
    void endTurn();
    int rollDice();
    void trade(Player *player, Resource give, Resource receive, int amount);
    
    // card actions
    void buyDevelopmentCard();
    void useMonopolyCard();
    void useYearOfPlentyCard();
    void useRoadBuildingCard();
    void useVictoryPointCard();

    void printPlayerStats();

private:
    string name;
    Board *board;
    Catan *game;
    int victoryPoints;
    int playerID;
    bool turn;
    bool hasRolled;

    unordered_map<Resource, int> resources;
    unordered_set<Building *> buildings;
    unordered_set<Building *> unbuiltSettlements;
    unordered_set<Building *> unbuiltRoads;
    unordered_set<Building *> unbuiltCities;
    unordered_set<Building *> startingSettlements;
    unordered_set<Building *> startingRoads;
    unordered_set<Card> developmentCards;

    // Helper functions
    bool canAfford(BuildingCost cost);
    void addResource(Resource resource, int amount);
    void removeResource(Resource resource, int amount);
    void deductCost(BuildingCost cost);
    void addVictoryPoints(int amount);
    void removeVictoryPoints(int amount);
    void collectResources(int diceRoll);
    void discardResources();

    static mt19937 rng; // Static member for RNG
};

#endif // PLAYER_HPP