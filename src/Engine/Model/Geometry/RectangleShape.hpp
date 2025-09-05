#pragma once
#include <vector>
#include "Vec2f.hpp"
#include "Shape.hpp"

class RectangleShape : public Shape {
public:
    RectangleShape(const Vec2f& size, Vec2f origin = {0.f, 0.f});

    Vec2f getSize() const;
    void setSize(const Vec2f& newSize);

private:
    Vec2f size;
    void buildVertices();
};
