#pragma once
#include <SFML/System/Vector2.hpp>
#include <vector>
#include <optional>
#include "Tile.hpp"

class TileMap {
public:
    TileMap(sf::Vector2f tileSize, const std::vector<std::vector<int>>& level, sf::Vector2f levelSize);
    std::vector<std::vector<Tile>> tiles;
    std::optional<Tile*> getTileAt(float x, float y);

    sf::Vector2f getTileSize() const { return tileSize; }
    sf::Vector2f getLevelSize() const { return levelSize; }

private:
sf::Vector2f tileSize;
sf::Vector2f levelSize;
};
