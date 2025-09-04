#include "Shape.hpp"

std::vector<Vec2f> Shape::getWorldVertices() const {
    std::vector<Vec2f> worldVerts;
    worldVerts.reserve(vertices.size());

    for (const auto& v : vertices) {
        // translation par la position,
        // mais corrigée de l’origine locale
        worldVerts.push_back(v + position - origin);
    }

    return worldVerts;
}
