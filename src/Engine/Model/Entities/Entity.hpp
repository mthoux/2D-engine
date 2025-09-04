#pragma once
#include "../Geometry/Vec2f.hpp"
#include "SFML/Graphics/Color.hpp"
#include "../Geometry/RectangleShape.hpp"
#include "../Components/Hitbox.hpp"
#include <algorithm>

#define MAX_VELOCITY 600.f
#define MIN_VELOCITY 0.f

class Entity {
public:
    Entity(); 
    Entity(Vec2f position, Vec2f size, sf::Color color = sf::Color::White, float velocity = 0.f);
    void move(const Vec2f& delta);

    void translate(const Vec2f& newPosition) {
        position = newPosition;
    }

    // Getters
    const Hitbox& getHitbox() const { return hitbox; }
    Vec2f getPosition() const { return position; }
    Vec2f getSize() const { return shape.getSize(); }
    sf::Color getColor() const { return color; }
    const RectangleShape& getShape() const { return shape; }
    float getVelocity() const { return velocity; }
    
    void setVelocity(float v) { 
        velocity = std::clamp(v, MIN_VELOCITY, MAX_VELOCITY);
    } 

private:
    Vec2f position;
    RectangleShape shape;
    sf::Color color;
    Hitbox hitbox;
    float velocity;
};
