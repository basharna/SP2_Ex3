#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <unordered_map>
#include <unordered_set>
#include "Resources.hpp"
#include "Building.hpp"

using namespace std;

class Player {
    public:
        Player(string name);

        // Getters
        string getName();
        int getVictoryPoints();
        int getResourceCount(Resource resource);
        unordered_set<Building*> getBuildings();

        // Setters
        void addResource(Resource resource, int amount);
        void removeResource(Resource resource, int amount);
        bool buildBuilding(Building* building);
        void removeBuilding(Building* building);

    private:
        string name;
        int victoryPoints;
        unordered_map<Resource, int> resources;
        unordered_set<Building*> buildings;
        unordered_set<Building*> unbuiltBuildings;

        // Helper functions
        void addVictoryPoints(int amount);
        void removeVictoryPoints(int amount);
        bool canAfford(BuildingCost cost);
        void deductCost(BuildingCost cost);

};

#endif // PLAYER_HPP