#include "Tile.hpp"

Tile::Tile() 
    : type(GRASS), position({0,0}), size({0,0}), color(sf::Color::White), walkable(true) 
{}

Tile::Tile(Type type, Vec2f position, Vec2f size, sf::Color color, bool walkable)
    : type(type), position(position), size(size), color(color), walkable(walkable) 
{}