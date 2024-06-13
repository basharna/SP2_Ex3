#ifndef BUILDING_HPP
#define BUILDING_HPP

#include "Resources.hpp"
#include <vector>
#include <string>

using namespace std;

class Player;

enum class BuildingType
{
    SETTLEMENT,
    STARTING_SETTLEMENT,
    CITY,
    ROAD,
    STARTING_ROAD
};

struct BuildingCost
{
    int wood;
    int brick;
    int wool;
    int wheat;
    int ore;
};

const BuildingCost SETTLEMENT_COST = {1, 1, 1, 1, 0};
const BuildingCost CITY_COST = {0, 0, 0, 2, 3};
const BuildingCost ROAD_COST = {1, 1, 0, 0, 0};

class Building
{
public:
    Building(BuildingType type, Player *owner);

    // Getters
    string getTypeString() const;
    BuildingType getType() const;
    Player *getOwner() const;
    BuildingCost getCost() const;
    bool isBuilt();
    vector<int> getVertexIds() const;
    bool isStartingBuilding();
    string getPositionString();

        // Setters
    void setBuilt(bool built);
    void setVertexIds(const vector<int> &vertices);

    // operator <<
    friend ostream &operator<<(ostream &os, const Building &building);

private:
    BuildingType type;
    vector<int> vertices;
    Player *owner;
    BuildingCost cost;
    bool built;
    bool startingBuilding;
};

#endif // BUILDING_HPP