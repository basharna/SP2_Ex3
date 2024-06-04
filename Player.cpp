#include "Player.hpp"

Player::Player(string name) : name(name), victoryPoints(2)
{
    resources[Resource::WOOD] = 0;
    resources[Resource::BRICK] = 0;
    resources[Resource::WOOL] = 0;
    resources[Resource::WHEAT] = 0;
    resources[Resource::ORE] = 0;

    for (int i = 0; i < 3; i++)
    {
        unbuiltBuildings.insert(new Building(BuildingType::SETTLEMENT, this));
    }

    for (int i = 0; i < 4; i++)
    {
        unbuiltBuildings.insert(new Building(BuildingType::CITY, this));
    }

    for (int i = 0; i < 15; i++)
    {
        unbuiltBuildings.insert(new Building(BuildingType::ROAD, this));
    }
}

string Player::getName()
{
    return name;
}

int Player::getVictoryPoints()
{
    return victoryPoints;
}

int Player::getResourceCount(Resource resource)
{
    return resources[resource];
}

unordered_set<Building *> Player::getBuildings()
{
    return buildings;
}

void Player::addResource(Resource resource, int amount)
{
    resources[resource] += amount;
}

void Player::removeResource(Resource resource, int amount)
{
    resources[resource] -= amount;
}

bool Player::buildBuilding(Building *building)
{
    // check if player can afford building
    if (!canAfford(building->getCost()))
    {
        return false;
    }

    // deduct cost
    BuildingCost cost = building->getCost();
    deductCost(cost);

    // add victory points
    if (building->getType() == BuildingType::SETTLEMENT)
    {
        addVictoryPoints(1);
    }
    else if (building->getType() == BuildingType::CITY)
    {
        addVictoryPoints(2);
    }

    buildings.insert(building);
    unbuiltBuildings.erase(building);

    return true;
}

void Player::removeBuilding(Building *building)
{
    // remove victory points
    if (building->getType() == BuildingType::SETTLEMENT)
    {
        removeVictoryPoints(1);
    }
    else if (building->getType() == BuildingType::CITY)
    {
        removeVictoryPoints(2);
    }

    buildings.erase(building);
    unbuiltBuildings.insert(building);
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
