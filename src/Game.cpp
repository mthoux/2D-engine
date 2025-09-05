#include "Game.hpp"
#include "Utils/MapGenerator.hpp"
#include "Engine/Configurations.hpp"
#include <iostream>

#include <thread>
#include <chrono>


#include "Utils/Utils.hpp"

Game::Game()
    : window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Tilemap")
    , view(sf::Vector2f(WINDOW_WIDTH/2.f, WINDOW_HEIGHT/2.f), sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT))
    , tileMap({TILE_SIZE, TILE_SIZE}, generateMap(WINDOW_WIDTH/TILE_SIZE, WINDOW_HEIGHT/TILE_SIZE), {float(WINDOW_HEIGHT / TILE_SIZE), float(WINDOW_WIDTH / TILE_SIZE)})
    , mapper()
    , player({0,0}, RectangleShape({TILE_SIZE, TILE_SIZE}), sf::Color::Red, 230.f)
    , controller(tileMap, false)
{
    window.setFramerateLimit(60);

    // On remplit le vector d'ennemis
    opponents.emplace_back(Vec2f{TILE_SIZE*2, TILE_SIZE}, RectangleShape({TILE_SIZE, TILE_SIZE}), sf::Color::Yellow, 0.f);
    opponents.emplace_back(Vec2f{TILE_SIZE*4, TILE_SIZE*2}, RectangleShape({TILE_SIZE*2, TILE_SIZE}), sf::Color::Cyan, 0.f);
    opponents.emplace_back(Vec2f{TILE_SIZE*6, TILE_SIZE*6}, RectangleShape({TILE_SIZE/3, TILE_SIZE/3}), sf::Color::Magenta, 0.f);
}

void Game::run() {
    sf::Clock clock;
    while(window.isOpen()) {
        float dt = clock.restart().asSeconds();

        processEvents();
        update(dt);
        render();
    }
}

void Game::processEvents() {
    while(const std::optional event = window.pollEvent()) {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
            player.setVelocity(player.getVelocity() + 50);
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
            player.setVelocity(player.getVelocity() - 50);
        }

        if(event->is<sf::Event::Closed>())
            window.close();

        if(auto wheelEvent = event->getIf<sf::Event::MouseWheelScrolled>()) {
            float delta = wheelEvent->delta;
            delta = -delta;
            float zoomFactor = 1.0f + delta * 0.1f;
            if (zoomFactor > 0.0f) view.zoom(zoomFactor);
        }
    }
}

void Game::update(float dt) {
    Vec2f oldPos = player.getPosition();
    Vec2f delta = controller.handleInput(player, dt);
    Vec2f newPos = oldPos + delta;

    player.setPosition({newPos.x, oldPos.y}); // Test X
    bool collideX = false;
    for (const Entity& opp : opponents) {
        if (player.getHitbox().intersects(player.getPosition(), opp.getHitbox(), opp.getPosition())) {
            collideX = true;
        }
    }
    if (collideX) newPos.x = oldPos.x;

    player.setPosition({oldPos.x, newPos.y}); // Test Y
    bool collideY = false;
    for (const Entity& opp : opponents) {
        if (player.getHitbox().intersects(player.getPosition(), opp.getHitbox(), opp.getPosition())) {
            collideY = true;
        }
    }
    if (collideY) newPos.y = oldPos.y;

    player.setPosition(newPos); // Position finale corrigée
    // tu peux ajouter ici d'autres systèmes (collisions, IA, etc.)
}

void Game::render() {
    ++test_counter;
    //std::this_thread::sleep_for(std::chrono::seconds(1));
    RectangleShape r({50,50}, {25, 25});
    

    window.clear();
    window.setView(view);

    window.draw(mapper.vmap(tileMap));
    for (const auto& opp : opponents) {
        window.draw(mapper.vmap(opp.getShape(), opp.getPosition(), opp.getColor()));
        //window.draw(mapper.vmap(opp.getHitbox().getShape(), opp.getHitbox().getTransform()->getPosition(), sf::Color::White));
    }
    window.draw(mapper.vmap(applyTransform(player.getShape(), Transform({0,0}, Transform::degToRad(test_counter), {1,1})), player.getPosition(), player.getColor()));
    window.draw(mapper.vmap(applyTransform(r,Transform({0,0},Transform::degToRad(test_counter),{2,2})), {TILE_SIZE*3, TILE_SIZE*3}, sf::Color::White));
    //window.draw(mapper.vmap( player.getHitbox().getShape(), player.getHitbox().getTransform()->getPosition(), sf::Color::Magenta));

    window.display();
}
