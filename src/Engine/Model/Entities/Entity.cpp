#include "Entity.hpp"

Entity::Entity()
    : shape({0,0}, {0,0}), color(sf::Color::White), hitbox(shape)
{}

Entity::Entity(Vec2f position, Vec2f size, sf::Color color) 
    : shape(position, size), color(color), hitbox(shape)
{}

void Entity::move(const Vec2f& delta) { translate(getPosition() + delta); }
