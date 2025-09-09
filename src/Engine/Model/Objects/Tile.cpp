#include "Tile.hpp"

// Constructeur par défaut
Tile::Tile() 
    : WorldObject(RectangleShape({0.f, 0.f}), Transform()),
      type(GRASS),
      color(sf::Color::White),
      walkable(true)
{}

// Constructeur avec paramètres
Tile::Tile(Type type, const Vec2f& position, const Vec2f& size, sf::Color color, bool walkable)
    : WorldObject(RectangleShape({0.f, 0.f}), position, size),
      type(type),
      color(color),
      walkable(walkable)
{}
