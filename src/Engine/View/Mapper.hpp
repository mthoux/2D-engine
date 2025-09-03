#pragma once
#include "../Model/Tile.hpp"
#include "../Model/TileMap.hpp"
#include "../Model/Entity.hpp"
#include "VertexObject.hpp"

class Mapper {
public:
    VertexObject vmap(Tile tile);
    VertexObject vmap(TileMap tileMap);
    VertexObject vmap(Entity entity);
private:

};