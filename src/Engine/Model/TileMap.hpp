#pragma once
#include <SFML/System/Vector2.hpp>
#include <vector>
#include "Tile.hpp"

class TileMap {
public:
    TileMap(sf::Vector2f tileSize, const std::vector<std::vector<int>>& level, sf::Vector2f levelSize);
    sf::Vector2f levelSize;
    std::vector<std::vector<Tile>> tiles;

private:
};
