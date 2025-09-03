#pragma once
#include <SFML/System/Vector2.hpp>
#include <vector>

class Shape {
public:
    Shape() = default;
    Shape(const std::vector<sf::Vector2f>& vertices, sf::Vector2f position = {0.f, 0.f});

    void setPosition(const sf::Vector2f& pos);
    sf::Vector2f getPosition() const;
    const std::vector<sf::Vector2f>& getVertices() const;
    std::vector<sf::Vector2f> getWorldVertices() const;

private:
    std::vector<sf::Vector2f> vertices; // sommets en coordonnées locales
    sf::Vector2f position;              // position dans le monde
};
