#include "Tile.hpp"

Tile::Tile() 
    : type(GRASS), shape({0,0}, {0,0}), color(sf::Color::White), walkable(true) 
{}

Tile::Tile(Type type, Vec2f position, Vec2f size, sf::Color color, bool walkable)
    : type(type), position(position), shape(size, {0,0}), color(color), walkable(walkable) 
{}