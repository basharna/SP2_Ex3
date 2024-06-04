#ifndef VERTEX_HPP
#define VERTEX_HPP

#include "Building.hpp"
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class Edge;
class Tile;

class Vertex
{
public:
    Vertex(int id);

    // Getters
    int getId();
    vector<Edge *> getEdges();
    vector<Tile *> getTiles();
    bool getBuilding();

    // Setters
    void setBuilding(Building *building);

    // Adders
    void addEdge(Edge *edge);
    void addTile(Tile *tile);

private:
    int id;
    unordered_set<Edge *> edges;
    unordered_set<Tile *> tiles;
    Building *building;
};

#endif // VERTEX_HPP