#include "EntityController.hpp"
#include <cmath>
#include "../Configurations.hpp"
#include "../Model/Entities/Tile.hpp"

EntityController::EntityController(TileMap& map) : map(&map) {}

void EntityController::handleInput(Entity& entity) {
    sf::Vector2f delta(0.f, 0.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::KEY_UP)) delta.y -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::KEY_DOWN)) delta.y += 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::KEY_LEFT)) delta.x -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::KEY_RIGHT)) delta.x += 1.f;

    // Normalize delta to have consistent speed in all directions
    if (delta.x != 0.f || delta.y != 0.f) {
        float len = std::sqrt(delta.x*delta.x + delta.y*delta.y);
        delta /= len;
        delta *= float(PIXELS_DISPLACEMENT);
    }

    sf::Vector2f nextPos = entity.getPosition() + delta;
    
    // auto tile = map.getTileAt(nextPos.x, nextPos.y);
    // if (tile && (*tile)->isWalkable()) {
    //     entity.move(delta);
    // }

    entity.move(delta);
}
