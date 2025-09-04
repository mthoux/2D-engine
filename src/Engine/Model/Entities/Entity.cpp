#include "Entity.hpp"

Entity::Entity()
    : position({0,0}), shape({0,0}, {0,0}), color(sf::Color::White), hitbox(shape), velocity(0.f)
{}

Entity::Entity(Vec2f position, Vec2f size, sf::Color color, float velocity) 
    : position(position), shape(size, {0,0}), color(color), hitbox(shape), velocity(velocity)
{}

void Entity::move(const Vec2f& delta) { translate(getPosition() + delta); }
