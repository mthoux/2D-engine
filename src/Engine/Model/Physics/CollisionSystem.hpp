#pragma once
#include <vector>
#include "../Objects/Entity.hpp"
#include "../Core/Math/Vec2f.hpp"

namespace Physics {

class CollisionSystem {
public:
    // Vérifie si une position donnée collide avec un ensemble d'entités
    static bool checkCollision(const Hitbox& playerHitbox, const Transform& playerTransform, const std::vector<Entity>& opponents);

    // Résout les collisions sur X et Y avec glissement
    static Vec2f resolveCollisions(const Vec2f& oldPos, const Vec2f& desiredPos,
                                         const Hitbox& playerHitbox, Transform& playerTransform,
                                         const std::vector<Entity>& opponents, float step);
};

} // namespace Physics
