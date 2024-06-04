#include "Edge.hpp"

Edge::Edge(Vertex* vertex1, Vertex* vertex2){
    this->vertex1 = vertex1;
    this->vertex2 = vertex2;
    this->building = nullptr;
}

Vertex* Edge::getVertex1(){
    return this->vertex1;
}

Vertex* Edge::getVertex2(){
    return this->vertex2;
}

Building* Edge::getBuilding(){
    return this->building;
}

void Edge::setBuilding(Building* building){
    if (building->getType() == BuildingType::ROAD){
        this->building = building;
    }
}
