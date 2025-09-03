#pragma once
#include <vector>
#include "Vec2f.hpp"
#include "Shape.hpp"

class RectangleShape : public Shape {
public:
    RectangleShape(const Vec2f& position, const Vec2f& size);

    Vec2f getSize() const  {return size;}
    void setSize(const Vec2f& newSize);

private:
    Vec2f size;
    void updateVertices();
};

