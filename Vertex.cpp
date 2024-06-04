#include "Vertex.hpp"

Vertex::Vertex(int id)
{
    this->id = id;
    this->building = nullptr;
}

int Vertex::getId()
{
    return this->id;
}

vector<Edge *> Vertex::getEdges()
{
    vector<Edge *> edgeList;
    for (auto &edge : this->edges)
    {
        edgeList.push_back(edge);
    }
    return edgeList;
}

vector<Tile *> Vertex::getTiles()
{
    vector<Tile *> tileList;
    for (auto &tile : this->tiles)
    {
        tileList.push_back(tile);
    }
    return tileList;
}

bool Vertex::getBuilding()
{
    return this->building;
}

void Vertex::setBuilding(Building *building)
{
    if (building->getType() == BuildingType::SETTLEMENT || building->getType() == BuildingType::CITY)
    {
        this->building = building;
    }
}

void Vertex::addEdge(Edge *edge)
{
    if (find(this->edges.begin(), this->edges.end(), edge) == this->edges.end())
    {
        this->edges.insert(edge);
    }
}

void Vertex::addTile(Tile *tile)
{
    if (find(this->tiles.begin(), this->tiles.end(), tile) == this->tiles.end())
    {
        this->tiles.insert(tile);
    }
}
