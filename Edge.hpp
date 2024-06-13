#ifndef EDGE_HPP
#define EDGE_HPP

#include "Vertex.hpp"
#include "Building.hpp"
#include <iostream>

class Edge
{
public:
    Edge(Vertex *vertex1, Vertex *vertex2);

    // Getters
    Vertex *getVertex1() const;
    Vertex *getVertex2() const;
    bool hasBuilding() const;
    bool hasBuilding(Player *player) const; 

    // Setters
    void addBuilding(Building *building);

    // operator <<
    friend ostream &operator<<(ostream &os, const Edge &edge);

private:
    Vertex *vertex1;
    Vertex *vertex2;
    Building *building;
};

#endif // EDGE_HPP