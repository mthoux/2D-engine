#pragma once
#include "../Math/Vec2f.hpp"
#include <vector>

class Shape {
public:
    Shape(const std::vector<Vec2f>& vertices,
          Vec2f offset = {0.f, 0.f})
        : vertices(vertices), offset(offset) {}

    Shape(Vec2f offset = {0.f, 0.f})
        : offset(offset) {}
    
    Vec2f getOffset() const { return offset; }
    const std::vector<Vec2f>& getVertices() const { return vertices; }

    void setOffset(const Vec2f& o) { offset = o; }

protected:
    std::vector<Vec2f> vertices; // sommets en coordonnées locales
    Vec2f offset;                // offset pour le dessin
};
