#ifndef EDGE_HPP
#define EDGE_HPP

#include "Vertex.hpp"
#include "Building.hpp"

class Edge {
    public:
        Edge(Vertex* vertex1, Vertex* vertex2);

        // Getters
        Vertex* getVertex1();
        Vertex* getVertex2();
        Building* getBuilding();

        // Setters
        void setBuilding(Building* building);

    private:
        Vertex* vertex1;
        Vertex* vertex2;
        Building* building;
};

#endif // EDGE_HPP