#pragma once

#include <optional>
#include <vector>
#include "../Core/Math/Vec2f.hpp"
#include "../Core/Geometry/Shape.hpp"
#include "../Core/Transform.hpp"
#include "../Objects/Entity.hpp"

class CollisionSystem2 {
public:

    static bool isOverlaping(const Shape& shape1, const Shape& shape2);
    static std::optional<Vec2f> getMTV(const Shape& shape1, const Shape& shape2);

};
