#include "EntityController.hpp"
#include <cmath>
#include "ControllerConfigurations.hpp"
#include "../Model/Core/Math/Vec2f.hpp"

EntityController::EntityController(TileMap& map, bool gridMode)
    : map(&map), useGridMovement(gridMode) {}

Vec2f EntityController::handleInput(Entity& entity, float dt) {
    Vec2f delta(0.f, 0.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::KEY_UP))    delta.y -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::KEY_DOWN))  delta.y += 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::KEY_LEFT))  delta.x -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::KEY_RIGHT)) delta.x += 1.f;

    if (delta.x == 0.f && delta.y == 0.f) return {0.f, 0.f};

    float len = std::sqrt(delta.x * delta.x + delta.y * delta.y);
    delta /= len;                  // normalisation
    delta *= entity.getVelocity() * dt;

    return delta;
}

