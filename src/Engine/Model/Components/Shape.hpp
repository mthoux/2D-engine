#pragma once
#include "Vec2f.hpp"
#include <vector>
#include <SFML/Graphics/Color.hpp>

class Shape {
public:
    Shape() = default;
    Shape(const std::vector<Vec2f>& vertices, Vec2f position = {0.f, 0.f}, sf::Color color = sf::Color::White)
        : vertices(vertices), position(position), color(color) {};
    Shape(Vec2f position = {0.f, 0.f}, sf::Color color = sf::Color::White)
        : position(position), color(color) {};

    void setPosition(const Vec2f& pos);
    Vec2f getPosition() const;
    const std::vector<Vec2f>& getVertices() const;
    std::vector<Vec2f> getWorldVertices() const;

protected:
    std::vector<Vec2f> vertices; // sommets en coordonnées locales
    Vec2f position;              // position dans le monde
    sf::Color color;
};
