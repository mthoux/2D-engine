#include "RectangleShape.hpp"

// Constructeur
RectangleShape::RectangleShape(Vec2f bottomLeftCorner, Vec2f topRightCorner) {
    vertices.clear();
    vertices.push_back({bottomLeftCorner.x, topRightCorner.y});
    vertices.push_back(topRightCorner);
    vertices.push_back({topRightCorner.x, bottomLeftCorner.y});
    vertices.push_back(bottomLeftCorner);
}

RectangleShape::RectangleShape(Vec2f origin)
    : Shape(origin)
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
    vertices.push_back({1.f, 0.f});            // top-right
    vertices.push_back({1.f, 1.f});         // bottom-right
    vertices.push_back({0.f, 1.f});            // bottom-left
}

bool RectangleShape::contains(const Vec2f& point) {
    float minX = std::min(vertices[0].x, vertices[2].x);
    float maxX = std::max(vertices[0].x, vertices[2].x);
    float minY = std::min(vertices[0].y, vertices[2].y);
    float maxY = std::max(vertices[0].y, vertices[2].y);

    return (point.x >= minX && point.x <= maxX &&
            point.y >= minY && point.y <= maxY);
}
