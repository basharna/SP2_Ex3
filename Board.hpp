#ifndef BOARD_HPP
#define BOARD_HPP

#include "Vertex.hpp"
#include "Edge.hpp"
#include "Tile.hpp"
#include <unordered_map>
#include <unordered_set>

class Board
{
public:
    static Board &getInstance();

    void addVertex(int id);
    void addEdge(int vertex1, int vertex2);
    void addTile(int id, Resource resource, int token, const vector<int> &vertices);
    void addBuilding(Building *building);
    Vertex *getVertex(int id);
    Tile *getTile(int id);

private:
    Board();
    unordered_map<int, Vertex *> vertices;
    unordered_set<Edge *> edges;
    unordered_map<int, Tile *> tiles;
    unordered_set<Building*> buildings;
};

#endif // BOARD_HPP