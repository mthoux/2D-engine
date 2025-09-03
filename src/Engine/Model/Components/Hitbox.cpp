#include "Hitbox.hpp"
#include <algorithm>

// Constructeurs
Hitbox::Hitbox() : Shape() {}

Hitbox::Hitbox(const std::vector<Vec2f>& vertices, Vec2f pos)
    : Shape(vertices, pos) {}

Hitbox::Hitbox(Vec2f pos, Vec2f size) {
    position = pos;
    vertices = {
        {0.f, 0.f},
        {size.x, 0.f},
        {size.x, size.y},
        {0.f, size.y}
    };
}

// Collision AABB simple
bool Hitbox::intersects(const Shape& other) const {
    auto vertsA = getWorldVertices();
    auto vertsB = other.getWorldVertices();

    float minAX = vertsA[0].x, maxAX = vertsA[0].x;
    float minAY = vertsA[0].y, maxAY = vertsA[0].y;

    for (const auto& v : vertsA) {
        minAX = std::min(minAX, v.x);
        maxAX = std::max(maxAX, v.x);
        minAY = std::min(minAY, v.y);
        maxAY = std::max(maxAY, v.y);
    }

    float minBX = vertsB[0].x, maxBX = vertsB[0].x;
    float minBY = vertsB[0].y, maxBY = vertsB[0].y;

    for (const auto& v : vertsB) {
        minBX = std::min(minBX, v.x);
        maxBX = std::max(maxBX, v.x);
        minBY = std::min(minBY, v.y);
        maxBY = std::max(maxBY, v.y);
    }

    return !(maxAX < minBX || minAX > maxBX || maxAY < minBY || minAY > maxBY);
}
