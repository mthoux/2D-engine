#pragma once
#include <vector>
#include <optional>
#include "Tile.hpp"
#include "../Components/Vec2f.hpp"

class TileMap {
public:
    TileMap(Vec2f tileSize, const std::vector<std::vector<int>>& level, Vec2f levelSize);
    std::vector<std::vector<Tile>> tiles;
    std::optional<Tile*> getTileAt(float x, float y);

    Vec2f getTileSize() const { return tileSize; }
    Vec2f getLevelSize() const { return levelSize; }

private:
Vec2f tileSize;
Vec2f levelSize;
};
