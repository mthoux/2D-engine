#include "EntityController.hpp"
#include <cmath>
#include "../Configurations.hpp"
#include "../Model/Entities/Tile.hpp"
#include "../Model/Components/Vec2f.hpp"

EntityController::EntityController(TileMap& map) : map(&map) {}

void EntityController::handleInput(Entity& entity) {
    Vec2f delta(0.f, 0.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::KEY_UP)) delta.y -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::KEY_DOWN)) delta.y += 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::KEY_LEFT)) delta.x -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::KEY_RIGHT)) delta.x += 1.f;

    
    // Normaliser pour vitesse constante en diagonale
    if (delta.x != 0.f || delta.y != 0.f) {
        float len = std::sqrt(delta.x * delta.x + delta.y * delta.y);
        delta /= len;
        delta *= float(PIXELS_DISPLACEMENT);
        entity.move(delta);
    }
}
