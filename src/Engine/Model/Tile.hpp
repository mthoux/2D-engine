#pragma once
#include <SFML/System/Vector2.hpp>
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
    Tile(Type type, sf::Vector2f position, sf::Vector2f size, sf::Color color = sf::Color::White, bool walkable = true);

    sf::Vector2f getPosition() const { return position; }
    sf::Vector2f getSize() const { return size; }
    sf::Color   getColor() const { return color; }
    Type        getType() const { return type; }
    bool        isWalkable() const { return walkable; }

private:
Type type;
sf::Vector2f position;
sf::Vector2f size;
sf::Color color;
bool walkable;
};