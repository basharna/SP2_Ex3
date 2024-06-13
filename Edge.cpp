#include "Edge.hpp"

Edge::Edge(Vertex *vertex1, Vertex *vertex2)
{
    this->vertex1 = vertex1;
    this->vertex2 = vertex2;
    this->building = nullptr;
}

Vertex *Edge::getVertex1() const
{
    return this->vertex1;
}

Vertex *Edge::getVertex2() const
{
    return this->vertex2;
} 

bool Edge::hasBuilding() const
{
    return this->building != nullptr;
}

bool Edge::hasBuilding(Player *player) const
{
    if (this->building == nullptr)
    {
        return false;
    }
    return this->building->getOwner() == player;
}

void Edge::addBuilding(Building *building)
{
    if (building->getType() == BuildingType::ROAD || building->getType() == BuildingType::STARTING_ROAD)
    {
        this->building = building;
    }
}

ostream &operator<<(ostream &os, const Edge &edge)
{
    os << "Edge: " << edge.getVertex1()->getId() << " - " << edge.getVertex2()->getId();
    return os;
}
