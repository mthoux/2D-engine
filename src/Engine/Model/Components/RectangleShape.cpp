#include "RectangleShape.hpp"

// Constructeur
RectangleShape::RectangleShape(const Vec2f& position, const Vec2f& size, Vec2f origin)
    : Shape(position, origin), size(size)
{
    buildVertices();
}

// Getter
Vec2f RectangleShape::getSize() const {
    return size;
}

// Setter
void RectangleShape::setSize(const Vec2f& newSize) {
    size = newSize;
    buildVertices();
}

// Met à jour les vertices locales (centrées sur 0,0)
void RectangleShape::buildVertices() {
    vertices.clear();

    vertices.push_back({0.f, 0.f});               // top-left
    vertices.push_back({size.x, 0.f});            // top-right
    vertices.push_back({size.x, size.y});         // bottom-right
    vertices.push_back({0.f, size.y});            // bottom-left
}
