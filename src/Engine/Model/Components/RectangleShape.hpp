#pragma once
#include <vector>
#include "Vec2f.hpp"
#include "Shape.hpp"

class RectangleShape : public Shape {
public:
    RectangleShape(const Vec2f& position, const Vec2f& size, const sf::Color& color = sf::Color::White);

    Vec2f getSize() const;
    void setSize(const Vec2f& newSize);
    sf::Color getColor() const { return color; }

private:
    Vec2f size;
    void updateVertices();
};

