#include "Hitbox.hpp"
#include "../../../Utils/Utils.hpp"
#include <algorithm>

// Collision AABB simple
// bool Hitbox::intersects(const Shape& other) const {
//     auto vertsA = shape.getWorldVertices();
//     auto vertsB = other.getWorldVertices();

//     float minAX = vertsA[0].x, maxAX = vertsA[0].x;
//     float minAY = vertsA[0].y, maxAY = vertsA[0].y;

//     for (const auto& v : vertsA) {
//         minAX = std::min(minAX, v.x);
//         maxAX = std::max(maxAX, v.x);
//         minAY = std::min(minAY, v.y);
//         maxAY = std::max(maxAY, v.y);
//     }

//     float minBX = vertsB[0].x, maxBX = vertsB[0].x;
//     float minBY = vertsB[0].y, maxBY = vertsB[0].y;

//     for (const auto& v : vertsB) {
//         minBX = std::min(minBX, v.x);
//         maxBX = std::max(maxBX, v.x);
//         minBY = std::min(minBY, v.y);
//         maxBY = std::max(maxBY, v.y);
//     }

//     return !(maxAX < minBX || minAX > maxBX || maxAY < minBY || minAY > maxBY);
// }
