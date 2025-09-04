#pragma once
#include "../Model/Entities/Tile.hpp"
#include "../Model/Entities/TileMap.hpp"
#include "../Model/Entities/Entity.hpp"
#include "../Model/Components/Vec2f.hpp"
#include "../Model/Components/Shape.hpp"
#include <SFML/Graphics.hpp>

class Mapper {
public:
    sf::VertexArray vmap(const Tile& tile);
    sf::VertexArray vmap(const TileMap& tileMap);
    sf::VertexArray vmap(const Entity& entity);
    sf::VertexArray vmap(const Shape& shape, sf::Color color);

private:
    inline sf::Vector2f toSFML(const Vec2f& v) const {
        return sf::Vector2f(v.x, v.y);
    }
};
