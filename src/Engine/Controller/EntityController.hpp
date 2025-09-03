#pragma once
#include "../Model/Entity.hpp"
#include <SFML/Window/Keyboard.hpp>

class EntityController {
public:
    void handleInput(Entity& entity);
};
