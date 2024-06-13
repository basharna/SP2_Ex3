#ifndef RESOURCES_HPP
#define RESOURCES_HPP

#include <string>

using namespace std;

enum class Resource {
    WOOD,
    BRICK,
    WOOL,
    WHEAT,
    ORE,
    DESERT
};

string to_string(Resource r);

#endif // RESOURCES_HPP