#pragma once
#include "../Model/Entities/Tile.hpp"
#include "../Model/Entities/TileMap.hpp"
#include "../Model/Entities/Entity.hpp"
#include "VertexObject.hpp"
#include "../Model/Components/Vec2f.hpp"
#include <SFML/Graphics.hpp>

class Mapper {
public:
    VertexObject vmap(Tile tile);
    VertexObject vmap(TileMap tileMap);
    VertexObject vmap(Entity entity);
private:
    inline sf::Vector2f toSFML(const Vec2f& v) {
        return sf::Vector2f(v.x, v.y);
    }
};