#pragma once
#include "Shape.hpp"

class Hitbox {
public:
    Hitbox(Shape shape)
        : shape(shape) {}

    void translate(const Vec2f& pos) {
        shape.translate(pos);
    }

    // Collision avec une forme
    bool intersects(const Shape& other) const;
    const Shape& getShape() const { return shape; }
private:
    Shape shape;
};
