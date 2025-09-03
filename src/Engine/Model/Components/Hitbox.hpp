#pragma once
#include "Shape.hpp"

class Hitbox : public Shape {
public:
    // Constructeurs
    Hitbox();
    Hitbox(const std::vector<Vec2f>& vertices, Vec2f pos = {0.f, 0.f});
    Hitbox(Vec2f pos, Vec2f size);

    // Collision avec une forme
    bool intersects(const Shape& other) const;
};
