#include "Building.hpp"
#include "Player.hpp"

Building::Building(BuildingType type, Player *owner)
{
    this->type = type;
    this->owner = owner;
    this->built = false;
    switch (type)
    {
    case BuildingType::SETTLEMENT:
        this->cost = SETTLEMENT_COST;
        this->startingBuilding = false;
        break;
    case BuildingType::CITY:
        this->cost = CITY_COST;
        this->startingBuilding = false;
        break;
    case BuildingType::ROAD:
        this->cost = ROAD_COST;
        this->startingBuilding = false;
        break;
    case BuildingType::STARTING_SETTLEMENT:
        this->cost = {0, 0, 0, 0, 0};
        this->startingBuilding = true;
        break;
    case BuildingType::STARTING_ROAD:
        this->cost = {0, 0, 0, 0, 0};
        this->startingBuilding = true;
        break;
    }
}

string Building::getTypeString() const
{
    switch (this->type)
    {
    case BuildingType::SETTLEMENT:
        return "Settlement";
    case BuildingType::CITY:
        return "City";
    case BuildingType::ROAD:
        return "Road";
    case BuildingType::STARTING_SETTLEMENT:
        return "Settlement";
    case BuildingType::STARTING_ROAD:
        return "Road";
    default:
        return "Unknown";
    }
}

string Building::getPositionString()
{
    if (this->type == BuildingType::ROAD || this->type == BuildingType::STARTING_ROAD)
    {
        return "(" + to_string(this->vertices[0]) + "," + to_string(this->vertices[1]) + ")";
    }
    else if (this->type == BuildingType::SETTLEMENT || this->type == BuildingType::CITY || this->type == BuildingType::STARTING_SETTLEMENT)
    {
        return "(" + to_string(this->vertices[0]) + ")";
    }
    return "Unknown";
}

BuildingType Building::getType() const
{
    return this->type;
}

Player *Building::getOwner() const
{
    return this->owner;
}

BuildingCost Building::getCost() const
{
    return this->cost;
}

bool Building::isBuilt()
{
    return this->built;
}

void Building::setBuilt(bool built)
{
    this->built = built;
}

vector<int> Building::getVertexIds() const
{
    return this->vertices;
}

bool Building::isStartingBuilding()
{
    return this->startingBuilding;
}

void Building::setVertexIds(const vector<int> &vertices)
{
    this->vertices = vertices;
}

ostream &operator<<(ostream &os, const Building &building)
{
    Player *player = building.getOwner();
    os << player->getName() << " - " << building.getTypeString() << " ";
    for (const auto &vertex : building.getVertexIds())
    {
        os << vertex << " ";
    }
    os << endl;
    return os;
}