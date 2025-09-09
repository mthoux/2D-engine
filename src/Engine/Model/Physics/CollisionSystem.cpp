#include "CollisionSystem.hpp"
#include <cmath>
#include <iostream>

namespace Physics {

// Teste si la position testPos entre en collision avec une entité
bool CollisionSystem::checkCollision(const Hitbox& playerHitbox, const Transform& playerTransform, const std::vector<Entity>& opponents) {
    for (const auto& opp : opponents) {
        // On passe directement les transforms complets
        if (playerHitbox.intersects(playerTransform, opp.getHitbox(), opp.getTransform())) {
            return true;
        }
    }
    return false;
}

Vec2f CollisionSystem::resolveCollisions(const Vec2f& oldPos, const Vec2f& desiredPos,
                                         const Hitbox& playerHitbox, Transform& playerTransform,
                                         const std::vector<Entity>& opponents, float step) {
    Vec2f newPos = oldPos;
    Vec2f delta = desiredPos - oldPos;

    // ---- Axe X ----
    float remainingX = delta.x;
    while (std::fabs(remainingX) > 0.0f) {
        float moveX = (std::fabs(remainingX) < step) ? remainingX : step * (remainingX > 0 ? 1 : -1);
        newPos.x += moveX;
        playerTransform.setPosition(Vec2f(newPos.x, playerTransform.getPosition().y)); // update transform X

        if (checkCollision(playerHitbox, playerTransform, opponents)) {
            newPos.x -= moveX; // reculer si collision
            break;
        }
        remainingX -= moveX;
    }

    // ---- Axe Y ----
    float remainingY = delta.y;
    while (std::fabs(remainingY) > 0.0f) {
        float moveY = (std::fabs(remainingY) < step) ? remainingY : step * (remainingY > 0 ? 1 : -1);
        newPos.y += moveY;
        playerTransform.setPosition(Vec2f(playerTransform.getPosition().x, newPos.y)); // update transform Y

        if (checkCollision(playerHitbox, playerTransform, opponents)) {
            newPos.y -= moveY; // reculer si collision
            break;
        }
        remainingY -= moveY;
    }

    return newPos;
}

}