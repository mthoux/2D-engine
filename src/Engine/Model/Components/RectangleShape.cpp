#include "RectangleShape.hpp"

// Constructeur
RectangleShape::RectangleShape(const Vec2f& position, const Vec2f& size, const sf::Color& color)
    : Shape(position, color), size(size)
{
    updateVertices();
}

// Getter taille
Vec2f RectangleShape::getSize() const {
    return size;
}

// Setter taille
void RectangleShape::setSize(const Vec2f& newSize) {
    size = newSize;
    updateVertices();
}

// Recalcul des 4 sommets à partir de position + size
void RectangleShape::updateVertices() {
    vertices.clear();
    vertices.push_back(position); // top-left
    vertices.push_back({position.x + size.x, position.y}); // top-right
    vertices.push_back({position.x + size.x, position.y + size.y}); // bottom-right
    vertices.push_back({position.x, position.y + size.y}); // bottom-left
}