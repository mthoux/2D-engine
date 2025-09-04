#include <vector>
#include "../Engine/Model/Geometry/Shape.hpp"
#include "../Engine/Model/Geometry/Vec2f.hpp"

std::vector<Vec2f> computeWorldVertices(const Shape& shape, const Vec2f& position) {
    std::vector<Vec2f> shapeVertices = shape.getVertices();
    std::vector<Vec2f> worldVerts;
    worldVerts.reserve(shapeVertices.size());
    for (const auto& v : shapeVertices)
        worldVerts.push_back(v + position);
    return worldVerts;
}