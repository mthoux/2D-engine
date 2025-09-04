#pragma once
#include <SFML/Graphics.hpp>
#include "Model/Entities/TileMap.hpp"
#include "Model/Entities/Entity.hpp"
#include "Controller/EntityController.hpp"
#include "View/Mapper.hpp"

class Game {
public:
    Game();
    ~Game() = default;

    void run();

private:
    void processEvents();
    void update(float dt);
    void render();

    sf::RenderWindow window;
    sf::View view;

    TileMap tileMap;
    Mapper mapper;
    Entity player;
    Entity opponent;
    EntityController controller;
};
