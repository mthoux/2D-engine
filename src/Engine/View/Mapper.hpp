#pragma once
#include "../Model/Objects/Tile.hpp"
#include "../Model/Objects/TileMap.hpp"
#include "../Model/Objects/Entity.hpp"
#include "../Model/Core/Math/Vec2f.hpp"
#include "../Model/Core/Geometry/Shape.hpp"
#include "../Model/Core/Transform.hpp"
#include <SFML/Graphics.hpp>

class Mapper {
public:
    sf::VertexArray vmap(const TileMap& tileMap);
    sf::VertexArray vmap(const Shape& shape, const Transform& transform = Transform(), sf::Color color = sf::Color::White);

private:
    inline sf::Vector2f toSFML(const Vec2f& v) const {
        return sf::Vector2f(v.x, v.y);
    }
};