#pragma once
#include "Vec2f.hpp"
#include <SFML/Graphics/Color.hpp>

class Hitbox {
public:
    Hitbox(); 
    Hitbox(Vec2f position, Vec2f size, sf::Color color = sf::Color::White);
    void move(const Vec2f& delta);

    void setPosition(const Vec2f& newPosition);
    Vec2f getPosition() const;
    Vec2f getSize() const;
    sf::Color getColor() const;

private:
    Vectcorners;
    Vec2f position;
    Vec2f size;
    sf::Color color;
};
