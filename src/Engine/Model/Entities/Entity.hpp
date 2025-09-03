#pragma once
#include <SFML/Graphics.hpp>

class Entity {
public:
    Entity(); 
    Entity(sf::Vector2f position, sf::Vector2f size, sf::Color color = sf::Color::White);
    void move(const sf::Vector2f& delta);

    void setPosition(const sf::Vector2f& newPosition);
    sf::Vector2f getPosition() const;
    sf::Vector2f getSize() const;
    sf::Color getColor() const;

private:
    sf::Vector2f position;
    sf::Vector2f size;
    sf::Color color;
};
