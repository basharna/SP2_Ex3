#include "Board.hpp"

void Board::initVertices()
{
    vertices.clear();
    // Create the vertices
    for (int i = 0; i < 54; i++)
    {
        addVertex(i);
    }
}

void Board::initEdges()
{
    edges.clear();
    for (int i = 1; i <= 5; i += 2)
    {
        addEdge(i - 1, i);
        addEdge(i, i + 1);
    }

    for (int i = 8; i <= 14; i += 2)
    {
        addEdge(i - 1, i);
        addEdge(i, i + 1);
    }

    for (int i = 17; i <= 25; i += 2)
    {
        addEdge(i - 1, i);
        addEdge(i, i + 1);
    }

    for (int i = 28; i <= 36; i += 2)
    {
        addEdge(i - 1, i);
        addEdge(i, i + 1);
    }

    for (int i = 39; i <= 45; i += 2)
    {
        addEdge(i - 1, i);
        addEdge(i, i + 1);
    }

    for (int i = 48; i <= 52; i += 2)
    {
        addEdge(i - 1, i);
        addEdge(i, i + 1);
    }

    addEdge(0, 8);
    addEdge(7, 17);
    addEdge(16, 27);
    addEdge(28, 38);
    addEdge(39, 47);

    addEdge(6, 14);
    addEdge(15, 25);
    addEdge(26, 37);
    addEdge(36, 46);
    addEdge(45, 53);

    addEdge(2, 10);
    addEdge(4, 12);
    addEdge(9, 19);
    addEdge(11, 21);
    addEdge(13, 23);
    addEdge(18, 29);
    addEdge(20, 31);
    addEdge(22, 33);
    addEdge(24, 35);
    addEdge(30, 40);
    addEdge(32, 42);
    addEdge(34, 44);
    addEdge(41, 49);
    addEdge(43, 51);
}

void Board::initTiles()
{
    tiles.clear();
    addTile(0, Resource::ORE, 10, {0, 1, 2, 8, 9, 10});
    addTile(1, Resource::WOOL, 2, {2, 3, 4, 10, 11, 12});
    addTile(2, Resource::WOOD, 9, {4, 5, 6, 12, 13, 14});
    addTile(3, Resource::WHEAT, 12, {7, 8, 9, 17, 18, 19});
    addTile(4, Resource::BRICK, 6, {9, 10, 11, 19, 20, 21});
    addTile(5, Resource::WOOL, 4, {11, 12, 13, 21, 22, 23});
    addTile(6, Resource::BRICK, 10, {13, 14, 15, 23, 24, 25});
    addTile(7, Resource::WHEAT, 9, {16, 17, 18, 27, 28, 29});
    addTile(8, Resource::WOOD, 11, {18, 19, 20, 29, 30, 31});
    addTile(9, Resource::DESERT, 0, {20, 21, 22, 31, 32, 33});
    addTile(10, Resource::WOOD, 3, {22, 23, 24, 33, 34, 35});
    addTile(11, Resource::ORE, 8, {24, 25, 26, 35, 36, 37});
    addTile(12, Resource::WOOD, 8, {28, 29, 30, 38, 39, 40});
    addTile(13, Resource::ORE, 3, {30, 31, 32, 40, 41, 42});
    addTile(14, Resource::WHEAT, 4, {32, 33, 34, 42, 43, 44});
    addTile(15, Resource::WOOL, 5, {34, 35, 36, 44, 45, 46});
    addTile(16, Resource::BRICK, 5, {39, 40, 41, 47, 48, 49});
    addTile(17, Resource::WHEAT, 6, {41, 42, 43, 49, 50, 51});
    addTile(18, Resource::WOOL, 11, {43, 44, 45, 51, 52, 53});
}

Board::Board()
{
    buildings.clear();
    initVertices();
    initEdges();
    initTiles();
}

Board::~Board()
{
    for (auto const &vertex : vertices)
    {
        delete vertex.second;
    }

    for (auto const &edge : edges)
    {
        delete edge;
    }

    for (auto const &tile : tiles)
    {
        delete tile.second;
    }

    buildings.clear();
}

void Board::addVertex(int id)
{
    if (vertices.find(id) == vertices.end())
    {
        vertices[id] = new Vertex(id);
    }
    else
    {
        cerr << "Vertex " << id << " already exists." << endl;
    }
}

void Board::addEdge(int vertex1, int vertex2)
{
    if (vertices.find(vertex1) == vertices.end() || vertices.find(vertex2) == vertices.end())
    {
        cerr << "One or both vertices not found: " << vertex1 << ", " << vertex2 << endl;
        return;
    }
    Vertex *v1 = vertices[vertex1];
    Vertex *v2 = vertices[vertex2];

    Edge *edge = new Edge(v1, v2);

    v1->addEdge(edge);
    v2->addEdge(edge);
    this->edges.insert(edge);
}

void Board::addTile(int id, Resource resource, int token, const vector<int> &vertexIds)
{
    if (tiles.find(id) == tiles.end())
    {
        tiles[id] = new Tile(id, resource, token);
    }

    Tile *tile = tiles[id];

    for (int vertexId : vertexIds)
    {
        if (vertices.find(vertexId) == vertices.end())
        {
            return;
        }
        Vertex *vertex = vertices[vertexId];
        tile->addVertex(vertex);
        vertex->addTile(tile);
    }
}

bool Board::canBuildRoad(Building *building)
{
    if (building->isStartingBuilding())
    {
        return true;
    }
    vector<int> vertexIds = building->getVertexIds();
    if (vertexIds.size() != 2)
    {
        return false;
    }

    Vertex *v1 = vertices[vertexIds[0]];
    Vertex *v2 = vertices[vertexIds[1]];
    if (!v1 || !v2)
    {
        cerr << "Null vertex pointer: v1=" << v1 << ", v2=" << v2 << endl;
        return false;
    }
    Edge *edge = getEdge(v1, v2);
    if (!edge)
    {
        cerr << "Null edge pointer" << endl;
        return false;
    }
    Player *player = building->getOwner();
    if (!player)
    {
        cerr << "Null player pointer" << endl;
        return false;
    }

    // check if there is a road at the edge
    if (edge->hasBuilding())
    {
        cout << "Edge already has a building" << endl;
        return false;
    }

    // check if player has a settlement or city at either vertex
    if (!v1->hasBuilding(player) && !v2->hasBuilding(player))
    {
        cout << "No building at either vertex" << endl;
        return false;
    }

    // check if player has a road at a neighboring edge
    for (auto &e : v1->getEdges())
    {
        if (e->hasBuilding(player))
        {
            return true;
        }
    }

    for (auto &e : v2->getEdges())
    {
        if (e->hasBuilding(player))
        {
            return true;
        }
    }

    return false;
}

bool Board::buildRoad(Building *building)
{
    if (!canBuildRoad(building))
    {
        return false;
    }

    vector<int> vertexIds = building->getVertexIds();
    Vertex *v1 = vertices[vertexIds[0]];
    Vertex *v2 = vertices[vertexIds[1]];
    Edge *edge = getEdge(v1, v2);

    edge->addBuilding(building);
    this->buildings.insert(building);
    return true;
}

bool Board::canBuildSettlement(Building *building)
{

    vector<int> vertexIds = building->getVertexIds();
    if (vertexIds.size() != 1)
    {
        cout << "Invalid number of vertices" << endl;
        return false;
    }

    int vertexId = vertexIds[0];
    if (this->vertices.find(vertexId) == this->vertices.end())
    {
        cout << "Vertex not found" << endl;
        return false;
    }

    Vertex *vertex = this->vertices[vertexId];
    Player *player = building->getOwner();

    // check if there is a building at the vertex
    if (vertex->hasBuilding())
    {
        cout << "Vertex already has a building" << endl;
        return false;
    }

    // check if there is a settlement at a neighboring vertex
    for (auto &v : vertex->getAdjacentVertices())
    {
        if (v->hasBuilding())
        {
            cout << "Adjacent vertex already has a building" << endl;
            return false;
        }
    }

    // check if player has a road at a neighboring edge
    for (auto &e : vertex->getEdges())
    {
        if (e->hasBuilding(player))
        {
            return true;
        }
    }

    return false;
}

bool Board::buildSettlement(Building *building)
{
    if (!canBuildSettlement(building))
    {
        return false;
    }

    vector<int> vertexIds = building->getVertexIds();
    int vertexId = vertexIds[0];
    Vertex *v = vertices[vertexId];

    v->addBuilding(building);
    this->buildings.insert(building);
    return true;
}

bool Board::canBuildCity(Building *building)
{
    vector<int> vertexIds = building->getVertexIds();
    if (vertexIds.size() != 1)
    {
        return false;
    }

    Vertex *v = vertices[vertexIds[0]];
    Player *player = building->getOwner();

    // check if there is a settlement at the vertex
    if (!v->hasBuilding(player) && v->getBuilding()->getType() != BuildingType::SETTLEMENT)
    {
        cout << "No settlement at the vertex" << endl;
        return false;
    }

    return true;
}

bool Board::buildCity(Building *building)
{
    if (!canBuildCity(building))
    {
        cout << "Cannot build city" << endl;
        return false;
    }

    vector<int> vertexIds = building->getVertexIds();
    Vertex *v = vertices[vertexIds[0]];

    v->addBuilding(building);
    this->buildings.insert(building);

    // remove settlement at the same vertex from buildings
    for (auto it = buildings.begin(); it != buildings.end(); ++it)
    {
        if ((*it)->getType() == BuildingType::SETTLEMENT && (*it)->getVertexIds() == building->getVertexIds())
        {
            buildings.erase(it);
            break;
        }
    }

    return true;
}

Vertex *Board::getVertex(int id)
{
    if (vertices.find(id) == vertices.end())
    {
        return nullptr;
    }
    return vertices[id];
}

Edge *Board::getEdge(Vertex *vertex1, Vertex *vertex2)
{
    for (Edge *edge : edges)
    {
        if ((edge->getVertex1() == vertex1 && edge->getVertex2() == vertex2) ||
            (edge->getVertex1() == vertex2 && edge->getVertex2() == vertex1))
        {
            return edge;
        }
    }
    return nullptr;
}

Tile *Board::getTile(int id)
{
    if (tiles.find(id) == tiles.end())
    {
        return nullptr;
    }
    return tiles[id];
}

unordered_set<Building *> Board::getBuildings()
{
    return this->buildings;
}

ostream &operator<<(ostream &os, const Board &board)
{
    if ((board.buildings).size() == 0)
    {
        os << "No building have been build yet";
        return os;
    }
    for (auto const &building : board.buildings)
    {
        os << *building;
    }

    return os;
}
