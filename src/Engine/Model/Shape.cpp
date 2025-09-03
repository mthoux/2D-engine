#include "Shape.hpp"

Shape::Shape(const std::vector<sf::Vector2f>& vertices, sf::Vector2f position)
    : vertices(vertices), position(position) {}

void Shape::setPosition(const sf::Vector2f& pos) {
    position = pos;
}

sf::Vector2f Shape::getPosition() const {
    return position;
}

const std::vector<sf::Vector2f>& Shape::getVertices() const {
    return vertices;
}

std::vector<sf::Vector2f> Shape::getWorldVertices() const {
    std::vector<sf::Vector2f> worldVerts;
    worldVerts.reserve(vertices.size());

    for (const auto& v : vertices) {
        worldVerts.push_back(v + position);
    }

    return worldVerts;
}
