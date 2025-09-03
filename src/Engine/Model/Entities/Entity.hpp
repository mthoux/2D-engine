#pragma once
#include "../Components/Vec2f.hpp"
#include "SFML/Graphics/Color.hpp"
#include "../Components/RectangleShape.hpp"
#include "../Components/Hitbox.hpp"

class Entity {
public:
    Entity(); 
    Entity(Vec2f position, Vec2f size, sf::Color color = sf::Color::White);
    void move(const Vec2f& delta);

    void setPosition(const Vec2f& newPosition) { shape.setPosition(newPosition); }
    Vec2f getPosition() const { return shape.getPosition(); }
    Vec2f getSize() const { return shape.getSize(); }
    sf::Color getColor() const { return color; }

private:
    RectangleShape shape;
    sf::Color color;
    Hitbox hitbox;
};
