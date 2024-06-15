#include "Vertex.hpp"
#include "Edge.hpp"
#include "Tile.hpp" // Add this line to include the header file for the 'Tile' class

Vertex::Vertex(int id)
{
    this->id = id;
    this->building = nullptr;
}


int Vertex::getId() const
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

Building *Vertex::getBuilding()
{
    return this->building;
}

bool Vertex::hasBuilding(Player *player)
{
    if (this->building == nullptr)
    {
        return false;
    }
    return this->building->getOwner() == player;
}

bool Vertex::hasBuilding()
{
    return this->building != nullptr;
}

void Vertex::addBuilding(Building *building)
{
    if (building->getType() == BuildingType::SETTLEMENT || building->getType() == BuildingType::CITY || building->getType() == BuildingType::STARTING_SETTLEMENT)
    {
        this->building = building;
    }
}


void Vertex::addEdge(Edge *edge)
{
    if (this->edges.find(edge) == this->edges.end())
    {
        this->edges.insert(edge);
    }
}

void Vertex::addTile(Tile *tile)
{
    if (this->tiles.find(tile) == this->tiles.end())
    {
        this->tiles.insert(tile);
    }
}

ostream &operator<<(ostream &os, const Vertex &vertex)
{
    os << "Vertex: " << vertex.id << " ";
    for (auto &edge : vertex.edges)
    {
        os << *edge << " ";
    }
    return os;
}

vector<Vertex *> Vertex::getAdjacentVertices()
{
    vector<Vertex *> adjacentVertices;
    for (auto &edge : this->edges)
    {
        Vertex *v1 = edge->getVertex1();
        Vertex *v2 = edge->getVertex2();
        if (v1->getId() == this->id)
        {
            adjacentVertices.push_back(v2);
        }
        else
        {
            adjacentVertices.push_back(v1);
        }
    }
    return adjacentVertices;
}