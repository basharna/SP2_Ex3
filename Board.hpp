#ifndef BOARD_HPP
#define BOARD_HPP

#include "Vertex.hpp"
#include "Edge.hpp"
#include "Tile.hpp"
#include "Resources.hpp"
#include <unordered_map>
#include <unordered_set>

class Board
{
public:
    Board();
    ~Board();

    // Building
    bool buildSettlement(Building *building);
    bool buildRoad(Building *building);
    bool buildCity(Building *building);

    // Getters
    Vertex *getVertex(int id);
    Edge *getEdge(Vertex *vertex1, Vertex *vertex2);
    Tile *getTile(int id);
    unordered_set<Building *> getBuildings();

    // operator <<
    friend ostream &operator<<(ostream &os, const Board &board);

private:
    unordered_map<int, Vertex *> vertices;
    unordered_set<Edge *> edges;
    unordered_map<int, Tile *> tiles;
    unordered_set<Building *> buildings;

    void addVertex(int id);
    void addEdge(int vertex1, int vertex2);
    void addTile(int id, Resource resource, int token, const vector<int> &vertices);

    // initialize the board
    void initVertices();
    void initEdges();
    void initTiles();

    // helper functions
    bool canBuildSettlement(Building *building);
    bool canBuildRoad(Building *building);
    bool canBuildCity(Building *building);
};

#endif // BOARD_HPP