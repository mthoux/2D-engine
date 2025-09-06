#pragma once
#include "../Math/Vec2f.hpp"
#include <vector>

class Shape {
public:
    Shape(const std::vector<Vec2f>& vertices,
          Vec2f referencePoint = {0.f, 0.f})
        : vertices(vertices), referencePoint(referencePoint) {}

    Shape(Vec2f referencePoint = {0.f, 0.f})
        : referencePoint(referencePoint) {}
    
    Vec2f getReference() const { return referencePoint; }
    const std::vector<Vec2f>& getVertices() const { return vertices; }

    void setReference(const Vec2f& o) { referencePoint = o; }

protected:
    std::vector<Vec2f> vertices; // sommets en coordonnées locales
    Vec2f referencePoint;                // referencePoint pour le dessin
};
