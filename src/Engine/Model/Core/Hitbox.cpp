#include "Hitbox.hpp"
#include "../Utils/Utils.hpp"
#include <algorithm>
#include <vector>

bool Hitbox::intersects(const Transform& transform,
                        const Hitbox& other,
                        const Transform& otherTransform) const {
    // Applique transform + offset aux sommets locaux
    std::vector<Vec2f> worldVertices1 = applyTransform(shape, transform).getVertices();
    std::vector<Vec2f> worldVertices2 = applyTransform(other.shape, otherTransform).getVertices();

    // Calcul AABB pour worldVertices1
    float minX1 = worldVertices1[0].x, maxX1 = worldVertices1[0].x;
    float minY1 = worldVertices1[0].y, maxY1 = worldVertices1[0].y;
    for (const auto& v : worldVertices1) {
        minX1 = std::min(minX1, v.x);
        maxX1 = std::max(maxX1, v.x);
        minY1 = std::min(minY1, v.y);
        maxY1 = std::max(maxY1, v.y);
    }

    // Calcul AABB pour worldVertices2
    float minX2 = worldVertices2[0].x, maxX2 = worldVertices2[0].x;
    float minY2 = worldVertices2[0].y, maxY2 = worldVertices2[0].y;
    for (const auto& v : worldVertices2) {
        minX2 = std::min(minX2, v.x);
        maxX2 = std::max(maxX2, v.x);
        minY2 = std::min(minY2, v.y);
        maxY2 = std::max(maxY2, v.y);
    }

    // Test chevauchement
    bool overlapX = maxX1 >= minX2 && minX1 <= maxX2;
    bool overlapY = maxY1 >= minY2 && minY1 <= maxY2;

    return overlapX && overlapY;
}
