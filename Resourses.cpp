#include "Resources.hpp"

string to_string(Resource r){
    switch(r){
        case Resource::WOOD:
            return "Wood";
        case Resource::BRICK:
            return "Brick";
        case Resource::WOOL:
            return "Wool";
        case Resource::WHEAT:
            return "Wheat";
        case Resource::ORE:
            return "Ore";
        case Resource::DESERT:
            return "Desert";
    }
}