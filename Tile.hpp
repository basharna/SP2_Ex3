#ifndef TILE_HPP
#define TILE_HPP

#include "Vertex.hpp"
#include <vector>

class Tile {
    public:
        Tile(int id, Resource resource, int token);
        
        // Getters
        int getId();
        vector<Vertex*> getVertices();
        Resource getResource();
        int getToken();

        // Setters
        void setId(int id);
        void setResource(Resource resource);
        void setToken(int token);

        // Adders
        void addVertex(Vertex* vertex);

    private:
        int id;
        unordered_map<int, Vertex*> vertices;
        Resource resource;
        int token;
};

#endif // TILE_HPP