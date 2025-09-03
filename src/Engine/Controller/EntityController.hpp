#pragma once
#include "../Model/Entities/Entity.hpp"
#include <SFML/Window/Keyboard.hpp>
#include "../Model/Entities/TileMap.hpp"

class EntityController {
public:
    void handleInput(Entity& entity);

    EntityController(TileMap& map);

private:
    TileMap* map;
};
