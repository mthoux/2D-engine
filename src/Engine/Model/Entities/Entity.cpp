#include "Entity.hpp"

Entity::Entity()
    : shape({0,0}, {0,0}, sf::Color::White)
{}

Entity::Entity(Vec2f position, Vec2f size, sf::Color color) 
    : shape(position, size, color)
{}

void Entity::move(const Vec2f& delta) { setPosition(getPosition() + delta); }
