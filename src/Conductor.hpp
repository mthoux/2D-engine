#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Engine/Model/Objects/TileMap.hpp"
#include "Engine/Model/Objects/Entity.hpp"
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
};
