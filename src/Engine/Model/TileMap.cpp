#include "TileMap.hpp"
#include <iostream>

TileMap::TileMap(sf::Vector2f tileSize, const std::vector<std::vector<int>>& level, sf::Vector2f levelSize)
    : levelSize(levelSize)
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

            switch (tileType)
            {
            case 0:
                color = sf::Color::Black;
                type  = Tile::NONE;
                break;
            case 1:
                color = sf::Color::Green;
                type  = Tile::GRASS;
                break;
            case 2:
                color = sf::Color::Blue;
                type  = Tile::WATER;
                break;
            default:
                std::cerr << "Unknown tile type: " << tileType << "\n";
                break;
            }

            tiles[y][x] = Tile(type, {x * tileSize.x, y * tileSize.y}, tileSize, color);
        }
    }
}
