#pragma once

#include "../Model/Entities/Entity.hpp"
#include "../Model/Entities/TileMap.hpp"
#include "../Model/Components/Vec2f.hpp"
#include <SFML/Window/Keyboard.hpp>

class EntityController {
public:
    // Constructeur : map et mode snap-to-grid optionnel
    EntityController(TileMap& map, bool gridMode = false);

    // Gestion de l'entrée clavier pour une entité
    void handleInput(Entity& entity, float dt);

private:
    TileMap* map;           // Référence à la carte de tiles
    bool useGridMovement;   // Activer le snap à la grille
};
