#ifndef VERTEX_HPP
#define VERTEX_HPP

#include "Building.hpp"
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
using namespace std;

class Edge;
class Tile;

class Vertex
{
public:
    Vertex(int id);

    // Getters
    int getId() const;
    vector<Edge *> getEdges();
    vector<Tile *> getTiles();
    Building *getBuilding();
    bool hasBuilding(Player *player);
    bool hasBuilding();

    vector<Vertex *> getAdjacentVertices();

    // Setters
    void addBuilding(Building *building);

    // Adders
    void addEdge(Edge *edge);
    void addTile(Tile *tile);


    // operator <<
    friend ostream &operator<<(ostream &os, const Vertex &vertex);

private:
    int id;
    unordered_set<Edge *> edges;
    unordered_set<Tile *> tiles;
    Building *building;
};

#endif // VERTEX_HPP