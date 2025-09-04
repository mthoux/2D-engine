#pragma once
#include "Vec2f.hpp"
#include <vector>

class Shape {
public:
    Shape(const std::vector<Vec2f>& vertices,
          Vec2f position = {0.f, 0.f},
          Vec2f origin = {0.f, 0.f})
        : vertices(vertices), position(position), origin(origin) {}

    Shape(Vec2f position = {0.f, 0.f}, Vec2f origin = {0.f, 0.f})
        : position(position), origin(origin) {}
    
    Vec2f getOrigin() const { return origin; }
    Vec2f getPosition() const { return position; }
    const std::vector<Vec2f>& getVertices() const { return vertices; }

    void translate(const Vec2f& pos) { position = pos; }
    void setOrigin(const Vec2f& o) { origin = o; }

    std::vector<Vec2f> getWorldVertices() const;

protected:
    std::vector<Vec2f> vertices; // sommets en coordonnées locales
    Vec2f position;              // position dans le monde
    Vec2f origin;                // point de référence local
};
