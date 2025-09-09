#include "Entity.hpp"

// Constructeur par défaut
Entity::Entity()
    : WorldObject(Shape(), Transform()),
      color(sf::Color::White),
      hitbox(getShape()),
      velocity(0.f)
{}

// Constructeur avec paramètres
Entity::Entity(const Shape& shape,  const Transform& transform, sf::Color color, float velocity)
    : WorldObject(shape, transform),
      color(color),
      hitbox(getShape()),
      velocity(std::clamp(velocity, MIN_VELOCITY, MAX_VELOCITY))
{}

// Déplacement relatif
void Entity::move(const Vec2f& delta) {
    translate(delta); // utilise le helper de WorldObject
}

