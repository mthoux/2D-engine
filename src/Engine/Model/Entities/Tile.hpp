#pragma once
#include "../Components/Vec2f.hpp"
#include <SFML/Graphics/Color.hpp>

class Tile
{
public:
    enum Type { 
        NONE,
        GRASS, 
        WATER
    };
    Tile();
    Tile(Type type, Vec2f position, Vec2f size, sf::Color color = sf::Color::White, bool walkable = true);

    Vec2f getPosition() const { return position; }
    Vec2f getSize() const { return size; }
    sf::Color   getColor() const { return color; }
    Type        getType() const { return type; }
    bool        isWalkable() const { return walkable; }

private:
Type type;
Vec2f position;
Vec2f size;
sf::Color color;
bool walkable;
};