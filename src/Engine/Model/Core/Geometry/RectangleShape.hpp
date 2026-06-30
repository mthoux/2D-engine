#pragma once
#include <vector>
#include "../Math/Vec2f.hpp"
#include "Shape.hpp"

class RectangleShape : public Shape {
public:
    RectangleShape(Vec2f bottomLeftCorner, Vec2f topRightCorner);
    RectangleShape(Vec2f origin = {0.f, 0.f});

    Vec2f getSize() const;
    void setSize(const Vec2f& newSize);
    bool contains(const Vec2f& point);

private:
    Vec2f size;
    void buildVertices();
};
