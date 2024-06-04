#ifndef BUILDING_HPP
#define BUILDING_HPP

#include "Resources.hpp"

class Player;

enum class BuildingType {
    SETTLEMENT,
    CITY,
    ROAD
};

struct BuildingCost {
    int wood;
    int brick;
    int wool;
    int wheat;
    int ore;
};

const BuildingCost SETTLEMENT_COST = {1, 1, 1, 1, 0};
const BuildingCost CITY_COST = {0, 0, 0, 2, 3};
const BuildingCost ROAD_COST = {1, 1, 0, 0, 0};


class Building {
    public:
        Building(BuildingType type, Player* owner);

        // Getters
        BuildingType getType();
        Player* getOwner();
        BuildingCost getCost();

    private:
        BuildingType type;
        Player* owner;
        BuildingCost cost;
};

#endif // BUILDING_HPP