#include "Board.hpp"

Board::Board() {}

Board& Board::getInstance() {
    static Board instance;
    return instance;
}

void Board::addVertex(int id) {
    if (vertices.find(id) == vertices.end()) {
        vertices[id] = new Vertex(id);
    }
}

void Board::addEdge(int vertex1, int vertex2) {
    if (vertices.find(vertex1) == vertices.end() || vertices.find(vertex2) == vertices.end()) {
        return;
    }
    Vertex* v1 = vertices[vertex1];
    Vertex* v2 = vertices[vertex2];

    Edge* edge = new Edge(v1, v2);

    v1->addEdge(edge);
    v2->addEdge(edge);
}

void Board::addTile(int id, Resource resource, int token, const vector<int>& vertexIds) {
    if (tiles.find(id) == tiles.end()) {
        tiles[id] = new Tile(id, resource, token);
    }

    Tile* tile = tiles[id];

    for (int vertexId : vertexIds) {
        if (vertices.find(vertexId) == vertices.end()) {
            return;
        }
        Vertex* vertex = vertices[vertexId];
        tile->addVertex(vertex);
        vertex->addTile(tile);
    }
}

void Board::addBuilding(Building* building) {
    buildings.insert(building);
}

Vertex* Board::getVertex(int id) {
    if (vertices.find(id) == vertices.end()) {
        return nullptr;
    }
    return vertices[id];
}

Tile* Board::getTile(int id) {
    if (tiles.find(id) == tiles.end()) {
        return nullptr;
    }
    return tiles[id];
}
