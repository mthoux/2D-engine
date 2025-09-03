#include "Tile.hpp"

using namespace sf;

Tile::Tile() 
    : type(GRASS), position({0,0}), size({0,0}), color(sf::Color::White) 
{}

Tile::Tile(Type type, Vector2f position, Vector2f size, Color color)
    : type(type), position(position), size(size), color(color) 
{}