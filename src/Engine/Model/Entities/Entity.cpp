#include "Entity.hpp"

Entity::Entity()
    : position({0,0}), size({0,0}), color(sf::Color::White)
{}

Entity::Entity(sf::Vector2f position, sf::Vector2f size, sf::Color color) 
    : position(position), size(size), color(color)
{}

sf::Vector2f Entity::getPosition() const { return position; }
sf::Vector2f Entity::getSize() const { return size; }
sf::Color   Entity::getColor() const { return color; }
void Entity::move(const sf::Vector2f& delta) { position += delta; }
void Entity::setPosition(const sf::Vector2f& newPosition) { position = newPosition; }
