#pragma once
#include "../Components/Vec2f.hpp"
#include <SFML/Graphics/Color.hpp>
#include "../Components/RectangleShape.hpp"

class Tile
{
public:
    enum Type { 
        NONE,
        GRASS, 
        WATER
    };
    Tile();
    Tile(Type type, Vec2f position, Vec2f size, sf::Color color, bool walkable);

    Vec2f getPosition() const { return shape.getPosition(); }
    Vec2f getSize() const { return shape.getSize(); }
    RectangleShape getShape() const { return shape; }
    sf::Color   getColor() const { return color; }
    Type        getType() const { return type; }
    bool        isWalkable() const { return walkable; }

private:
Type type;
RectangleShape shape;
sf::Color color;
bool walkable;
};