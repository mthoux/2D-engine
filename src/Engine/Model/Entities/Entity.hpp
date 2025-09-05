#pragma once
#include "../WorldObject.hpp"
#include "../Components/Hitbox.hpp"
#include "SFML/Graphics/Color.hpp"
#include <algorithm>

#define MAX_VELOCITY 1600.f
#define MIN_VELOCITY 0.f

class Entity : public WorldObject {
public:
    // Constructeurs
    Entity();
    Entity(const Vec2f position, const Shape& shape, sf::Color color = sf::Color::White, float velocity = 0.f);

    // Déplacement
    void move(const Vec2f& delta);

    // Getters
    const Hitbox& getHitbox() const { return hitbox; }
    sf::Color getColor() const { return color; }
    float getVelocity() const { return velocity; }

    // Setter
    void setVelocity(float v) {
        velocity = std::clamp(v, MIN_VELOCITY, MAX_VELOCITY);
    }

private:
    Hitbox hitbox;
    sf::Color color;
    float velocity;
};
