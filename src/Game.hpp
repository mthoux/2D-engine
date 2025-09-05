#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Engine/Model/Entities/TileMap.hpp"
#include "Engine/Model/Entities/Entity.hpp"
#include "Engine/Controller/EntityController.hpp"
#include "Engine/View/Mapper.hpp"

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
    std::vector<Entity> opponents;
    EntityController controller;
    int test_counter = 0;
};
