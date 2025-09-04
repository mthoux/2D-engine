#pragma once
#include "Vec2f.hpp"
#include <vector>

class Shape {
public:
    Shape(const std::vector<Vec2f>& vertices, Vec2f position = {0.f, 0.f})
        : vertices(vertices), position(position) {};
    Shape(Vec2f position = {0.f, 0.f})
        : position(position) {};

    void translate(const Vec2f& pos);
    Vec2f getPosition() const;
    const std::vector<Vec2f>& getVertices() const;
    std::vector<Vec2f> getWorldVertices() const;

protected:
    std::vector<Vec2f> vertices; // sommets en coordonnées locales
    Vec2f position;              // position dans le monde
};
