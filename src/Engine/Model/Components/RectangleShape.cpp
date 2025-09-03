#include "RectangleShape.hpp"

RectangleShape::RectangleShape(const Vec2f& position, const Vec2f& size)
    : Shape(position), size(size)
{
    updateVertices();
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