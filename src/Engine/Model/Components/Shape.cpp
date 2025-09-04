#include "Shape.hpp"

void Shape::translate(const Vec2f& pos) {
    position = pos;
}

Vec2f Shape::getPosition() const {
    return position;
}

const std::vector<Vec2f>& Shape::getVertices() const {
    return vertices;
}

std::vector<Vec2f> Shape::getWorldVertices() const {
    std::vector<Vec2f> worldVerts;
    worldVerts.reserve(vertices.size());

    for (const auto& v : vertices) {
        worldVerts.push_back(v + position);
    }

    return worldVerts;
}
