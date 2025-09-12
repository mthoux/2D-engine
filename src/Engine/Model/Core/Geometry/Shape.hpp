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

    Vec2f project(const Vec2f& axis) const {
        float min = axis.dot(vertices[0]);
        float max = min;
        for (int i = 1; i < int(vertices.size()); i++) {
            float p = axis.dot(vertices[i]);
            if (p < min) min = p;
            else if (p > max) max = p;
        }

        return {min, max};
    }

    std::vector<Vec2f> getAxes() const {
        int verticesNumb = static_cast<int>(vertices.size());   
        std::vector<Vec2f> axis(verticesNumb);

        for (int i = 0; i < verticesNumb; i++) {
            const Vec2f& p1 = vertices[i];
            const Vec2f& p2 = vertices[(i + 1) % verticesNumb];
            Vec2f edge = p1 - p2;
            Vec2f normal(-edge.y, edge.x);
            axis[i] = normal.normalized();
        }
        return axis;
    }

    Vec2f getCenter() const {
        Vec2f center(0.f, 0.f);
        if (vertices.empty()) return center;

        for (const auto& v : vertices) {
            center += v;
        }

        center /= static_cast<float>(vertices.size());
        return center;
    }

protected:
    std::vector<Vec2f> vertices; // sommets en coordonnées locales
    Vec2f referencePoint;                // referencePoint pour le dessin
};
