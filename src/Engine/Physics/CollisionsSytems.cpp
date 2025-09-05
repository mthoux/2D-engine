#include "CollisionSystem.hpp"
#include <iostream>

void CollisionSystem::addEntity(Entity* entity) {
    entities.push_back(entity);
}

void CollisionSystem::handleCollisions(Entity& player) {
    Vec2f oldPos = player.getPosition();
    Vec2f newPos = oldPos;

    // On teste séparément X et Y pour permettre le glissement
    // Test X
    player.setPosition({oldPos.x, oldPos.y}); // au départ
    for (auto* e : entities) {
        if (player.getHitbox().intersects(e->getHitbox())) {
            newPos.x = oldPos.x; // rollback si collision
        }
    }

    // Test Y
    player.setPosition({newPos.x, oldPos.y});
    for (auto* e : entities) {
        if (player.getHitbox().intersects(e->getHitbox())) {
            newPos.y = oldPos.y; // rollback si collision
        }
    }

    player.setPosition(newPos);
}
