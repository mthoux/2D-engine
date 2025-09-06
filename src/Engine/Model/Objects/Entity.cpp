#include "Entity.hpp"

// Constructeur par défaut
Entity::Entity()
    : WorldObject({0.f, 0.f}, Shape()),
      color(sf::Color::White),
      hitbox(getShape(), {0.f, 0.f}),
      velocity(0.f)
{}

// Constructeur avec paramètres
Entity::Entity(const Vec2f position, const Shape& shape, sf::Color color, float velocity)
    : WorldObject(position, shape),
      color(color),
      hitbox(getShape(), {0.f, 0.f}),
      velocity(std::clamp(velocity, MIN_VELOCITY, MAX_VELOCITY))
{}

// Déplacement relatif
void Entity::move(const Vec2f& delta) {
    translate(delta); // utilise le helper de WorldObject
}

