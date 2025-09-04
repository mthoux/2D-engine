#pragma once
#include "../Model/Entities/Tile.hpp"
#include "../Model/Entities/TileMap.hpp"
#include "../Model/Entities/Entity.hpp"
#include "../Model/Geometry/Vec2f.hpp"
#include "../Model/Geometry/Shape.hpp"
#include <SFML/Graphics.hpp>

class Mapper {
public:
    sf::VertexArray vmap(const TileMap& tileMap);
    sf::VertexArray vmap(const Shape& shape, Vec2f position, sf::Color color);

private:
    inline sf::Vector2f toSFML(const Vec2f& v) const {
        return sf::Vector2f(v.x, v.y);
    }
};