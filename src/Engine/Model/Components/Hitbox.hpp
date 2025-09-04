#pragma once
#include "../Geometry/Shape.hpp"

class Hitbox {
public:
    Hitbox(Shape shape)
        : shape(shape) {}

    // Collision avec une forme
    //bool intersects(const Shape& other) const;
    const Shape& getShape() const { return shape; }
private:
    Shape shape;
};
