#include "RectangleShape.hpp"

// Constructeur
RectangleShape::RectangleShape(const Vec2f& position, const Vec2f& size)
    : Shape(position), size(size)
{
    updateVertices();
}

// Getter
Vec2f RectangleShape::getSize() const {
    return size;
}

// Setter
void RectangleShape::setSize(const Vec2f& newSize) {
    size = newSize;
    updateVertices();
}

// Met à jour les vertices locales (centrées sur 0,0)
void RectangleShape::updateVertices() {
    vertices.clear();

    float halfWidth  = size.x / 2.f;
    float halfHeight = size.y / 2.f;

    vertices.push_back({-halfWidth, -halfHeight}); // top-left
    vertices.push_back({ halfWidth, -halfHeight}); // top-right
    vertices.push_back({ halfWidth,  halfHeight}); // bottom-right
    vertices.push_back({-halfWidth,  halfHeight}); // bottom-left
}
