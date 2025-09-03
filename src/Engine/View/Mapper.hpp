#pragma once
#include "../Model/Entities/Tile.hpp"
#include "../Model/Entities/TileMap.hpp"
#include "../Model/Entities/Entity.hpp"
#include "VertexObject.hpp"

class Mapper {
public:
    VertexObject vmap(Tile tile);
    VertexObject vmap(TileMap tileMap);
    VertexObject vmap(Entity entity);
private:

};