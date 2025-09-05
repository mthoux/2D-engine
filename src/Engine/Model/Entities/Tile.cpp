#include "Tile.hpp"

// Constructeur par défaut
Tile::Tile() 
    : WorldObject({0.f, 0.f}, RectangleShape({0.f, 0.f}, {0.f, 0.f})),
      type(GRASS),
      color(sf::Color::White),
      walkable(true)
{}

// Constructeur avec paramètres
Tile::Tile(Type type, const Vec2f& position, const Vec2f& size, sf::Color color, bool walkable)
    : WorldObject(position, RectangleShape(size, {0.f, 0.f})), // Initialise position et shape via WorldObject
      type(type),
      color(color),
      walkable(walkable)
{}
