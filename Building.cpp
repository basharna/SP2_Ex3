#include "Building.hpp"

Building::Building(BuildingType type, Player* owner){
    this->type = type;
    this->owner = owner;
    switch (type){
        case BuildingType::SETTLEMENT:
            this->cost = SETTLEMENT_COST;
            break;
        case BuildingType::CITY:
            this->cost = CITY_COST;
            break;
        case BuildingType::ROAD:
            this->cost = ROAD_COST;
            break;
    }
}


BuildingType Building::getType(){
    return this->type;
}

Player* Building::getOwner(){
    return this->owner;
}

BuildingCost Building::getCost(){
    return this->cost;
}
