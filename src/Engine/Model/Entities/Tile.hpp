#pragma once
#include "../Geometry/Vec2f.hpp"
#include <SFML/Graphics/Color.hpp>
#include "../Geometry/RectangleShape.hpp"

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

    Vec2f getPosition() const { return position; }
    Vec2f getSize() const { return shape.getSize(); }
    const RectangleShape& getShape() const { return shape; }
    sf::Color   getColor() const { return color; }
    Type        getType() const { return type; }
    bool        isWalkable() const { return walkable; }

private:
    Vec2f position;
    Type type;
    RectangleShape shape;
    sf::Color color;
    bool walkable;
};