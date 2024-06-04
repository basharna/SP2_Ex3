#include "Tile.hpp"

Tile::Tile(int id, Resource resource, int token) : id(id), resource(resource), token(token) {}

int Tile::getId() {
    return id;
}

vector<Vertex*> Tile::getVertices() {
    vector<Vertex*> vertexList;
    for (auto& vertex : vertices) {
        vertexList.push_back(vertex.second);
    }
    return vertexList;
}

Resource Tile::getResource() {
    return resource;
}

int Tile::getToken() {
    return token;
}

void Tile::setId(int id) {
    this->id = id;
}

void Tile::setResource(Resource resource) {
    this->resource = resource;
}

void Tile::setToken(int token) {
    this->token = token;
}

void Tile::addVertex(Vertex* vertex) {
    if (vertices.find(vertex->getId()) == vertices.end()) {
        vertices[vertex->getId()] = vertex;
    }
}