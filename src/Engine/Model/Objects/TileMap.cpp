#include "TileMap.hpp"
#include <iostream>

TileMap::TileMap(Vec2f tileSize, const std::vector<std::vector<int>>& level, Vec2f levelSize)
    : tileSize(tileSize), levelSize(levelSize)
{
    int height = static_cast<int>(levelSize.x);
    int width  = static_cast<int>(levelSize.y);

    tiles.resize(height);
    for (int y = 0; y < height; ++y) {
        tiles[y].resize(width);
    }

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {

            int tileType = 0;
            if (y < static_cast<int>(level.size()) && x < static_cast<int>(level[y].size())) {
                tileType = level[y][x];
            } else {
                std::cerr << "Warning: accessing out-of-bounds tile at (" << x << "," << y << ")\n";
            }
            
            sf::Color color = sf::Color::Transparent;
            Tile::Type type = Tile::NONE;
            bool walkable = true;

            switch (tileType)
            {
            case 0:
                color = sf::Color::Black;
                type  = Tile::NONE;
                walkable = true;
                break;
            case 1:
                color = sf::Color::Green;
                type  = Tile::GRASS;
                walkable = true;
                break;
            case 2:
                color = sf::Color::Blue;
                type  = Tile::WATER;
                walkable = false;
                break;
            case 3:
                color = sf::Color::Yellow;
                type  = Tile::SAND;
                walkable = true;
                break;
            default:
                std::cerr << "Unknown tile type: " << tileType << "\n";
                break;
            }

            tiles[y][x] = Tile(type, {x * tileSize.x, y * tileSize.y}, tileSize, color, walkable);
        }
    }
}

std::optional<Tile*> TileMap::getTileAt(const Vec2f& position) {
    int tx = static_cast<int>(position.x / tileSize.x);
    int ty = static_cast<int>(position.y / tileSize.y);

    if (ty < 0 || ty >= tiles.size() || tx < 0 || tx >= tiles[0].size()) {
        std::cerr << "Warning: accessing out-of-bounds tile at (" << tx << "," << ty << ")\n";
        return std::nullopt;
    }

    return &tiles[ty][tx];
}