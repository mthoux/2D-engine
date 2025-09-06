#pragma once
#include <vector>
#include "../Core/Geometry/Shape.hpp"
#include "../Core/Math/Vec2f.hpp"
#include "../Core/Geometry/Shape.hpp"
#include "../Core/Transform.hpp"
#include "../Core/Math/Mat3.hpp"

inline std::vector<Vec2f> computeWorldVertices(const Shape& shape, const Vec2f& position) {
    std::vector<Vec2f> shapeVertices = shape.getVertices();
    std::vector<Vec2f> worldVerts;
    worldVerts.reserve(shapeVertices.size());
    for (const auto& v : shapeVertices)
        worldVerts.push_back(v - shape.getReference() + position);
    return worldVerts;
}


inline Shape applyTransform(const Shape& shape, const Transform& transform) {
    std::vector<Vec2f> transformedVertices;
    Mat3 mat = transform.getMatrix();

    for (const auto& v : shape.getVertices()) {
        // soustraire l'offset pour que la rotation/scale se fasse autour du pivot
        transformedVertices.push_back(mat.apply(v - shape.getReference()));
    }

    // Crée une nouvelle Shape avec les vertices transformées et le même offset
    Shape newShape(transformedVertices, shape.getReference());
    return newShape;
}

