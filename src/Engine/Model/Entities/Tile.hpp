#pragma once
#include "../Math/Vec2f.hpp"
#include <SFML/Graphics/Color.hpp>
#include "../Geometry/RectangleShape.hpp"
#include "../WorldObject.hpp"

class Tile : public WorldObject
{
public:
    enum Type { 
        NONE,
        GRASS, 
        WATER
    };

    // Constructeurs
    Tile();
    Tile(Type type, const Vec2f& position, const Vec2f& size, sf::Color color, bool walkable);

    // Getters
    sf::Color getColor() const { return color; }
    Type getType() const { return type; }
    bool isWalkable() const { return walkable; }

private:
    Type type;
    sf::Color color;
    bool walkable;
};
