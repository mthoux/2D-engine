#include "EntityController.hpp"
#include <cmath>
#include "../Configurations.hpp"
#include "../Model/Geometry/Vec2f.hpp"

EntityController::EntityController(TileMap& map, bool gridMode)
    : map(&map), useGridMovement(gridMode) {}

void EntityController::handleInput(Entity& entity, float dt) {
    Vec2f delta(0.f, 0.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::KEY_UP))    delta.y -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::KEY_DOWN))  delta.y += 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::KEY_LEFT))  delta.x -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::KEY_RIGHT)) delta.x += 1.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
        entity.setVelocity(entity.getVelocity() + 10);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        entity.setVelocity(entity.getVelocity() - 10);
    }

    // Rien à faire si pas de mouvement
    if (delta.x == 0.f && delta.y == 0.f) return;

    float len = std::sqrt(delta.x * delta.x + delta.y * delta.y);
    if (len > 0.f) {
        delta /= len;                   // normalisation
        delta *= entity.getVelocity() * dt;
    }

    if (useGridMovement) {
        // Snap à la grille
        Vec2f tileSize = map->getTileSize();
        int tileX = static_cast<int>(delta.x / tileSize.x);
        int tileY = static_cast<int>(delta.y / tileSize.y);
        delta = Vec2f(tileX * tileSize.x, tileY * tileSize.y);
    }

    // Appliquer le déplacement
    entity.translate(delta);
}
