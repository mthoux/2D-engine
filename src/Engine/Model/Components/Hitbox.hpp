#pragma once
#include "../Geometry/Shape.hpp"
#include "../Components/Transform.hpp"

class Hitbox {
public:
    Hitbox(const Transform& transform, const Shape& shape, const Vec2f& offset = {0.f, 0.f})
        : transform(transform), shape(shape), localOffset(offset) {}

    bool intersects(const Hitbox& other) const;

    const Shape& getShape() const { return shape; }
    const Transform& getTransform() const { return transform; }

private:
    const Transform& transform; // Position réel
    Shape shape;                // Forme (position local)
    Vec2f localOffset;          // Offset de la forme dans le monde
};
