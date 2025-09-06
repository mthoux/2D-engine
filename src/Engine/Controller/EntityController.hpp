#pragma once

#include "../Model/Objects/Entity.hpp"
#include "../Model/Objects/TileMap.hpp"
#include "../Model/Core/Math/Vec2f.hpp"
#include <SFML/Window/Keyboard.hpp>

class EntityController {
public:
    // Constructeur : map et mode snap-to-grid optionnel
    EntityController(TileMap& map, bool gridMode = false);

    // Gestion de l'entrée clavier pour une entité
    Vec2f handleInput(Entity& entity, float dt);

private:
    TileMap* map;           // Référence à la carte de tiles
    bool useGridMovement;   // Activer le snap à la grille
};
