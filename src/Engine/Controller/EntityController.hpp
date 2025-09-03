#pragma once
#include "../Model/Entity.hpp"
#include <SFML/Window/Keyboard.hpp>
#include "../Model/TileMap.hpp"

class EntityController {
public:
    void handleInput(Entity& entity);

    EntityController(TileMap& map);

private:
    TileMap* map;
};
