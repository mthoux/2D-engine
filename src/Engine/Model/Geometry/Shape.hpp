#pragma once
#include "Vec2f.hpp"
#include <vector>

class Shape {
public:
    Shape(const std::vector<Vec2f>& vertices,
          Vec2f origin = {0.f, 0.f})
        : vertices(vertices), origin(origin) {}

    Shape(Vec2f origin = {0.f, 0.f})
        : origin(origin) {}
    
    Vec2f getOrigin() const { return origin; }
    const std::vector<Vec2f>& getVertices() const { return vertices; }

    void setOrigin(const Vec2f& o) { origin = o; }

    std::vector<Vec2f> getWorldVertices() const;

protected:
    std::vector<Vec2f> vertices; // sommets en coordonnées locales
    Vec2f origin;                // point de référence local
};
