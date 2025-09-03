#include "RectangleShape.hpp"

RectangleShape::RectangleShape(const Vec2f& position, const Vec2f& size, const sf::Color& color)
    : Shape(position, color), size(size)
{
    updateVertices();
}

Vec2f RectangleShape::getSize() const {
    return size;
}

void RectangleShape::setSize(const Vec2f& newSize) {
    size = newSize;
    updateVertices();
}

void RectangleShape::updateVertices() {
    vertices.clear();
    vertices.push_back(position); // top-left
    vertices.push_back({position.x + size.x, position.y}); // top-right
    vertices.push_back({position.x + size.x, position.y + size.y}); // bottom-right
    vertices.push_back({position.x, position.y + size.y}); // bottom-left
}