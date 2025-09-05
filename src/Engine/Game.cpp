#include "Game.hpp"
#include "../Utils/MapGenerator.hpp"
#include "Configurations.hpp"
#include <iostream>

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
    Vec2f newPos = oldPos;

    // --- COLLISION X ---
    float moveX = delta.x;
    for (const Entity& opp : opponents) {
        if (player.getHitbox().intersectsX(newPos + Vec2f{moveX, 0}, opp.getHitbox(), opp.getPosition())) {
            if (delta.x > 0) // déplacement vers la droite
                moveX = std::min(moveX, opp.getHitbox().left(newPos) - player.getHitbox().right(newPos));
            else // déplacement vers la gauche
                moveX = std::max(moveX, opp.getHitbox().right(newPos) - player.getHitbox().left(newPos));
        }
    }
    newPos.x += moveX;

    // --- COLLISION Y ---
    float moveY = delta.y;
    for (const Entity& opp : opponents) {
        if (player.getHitbox().intersectsY(newPos + Vec2f{0, moveY}, opp.getHitbox(), opp.getPosition())) {
            if (delta.y > 0) // déplacement vers le bas
                moveY = std::min(moveY, opp.getHitbox().top(newPos) - player.getHitbox().bottom(newPos));
            else // déplacement vers le haut
                moveY = std::max(moveY, opp.getHitbox().bottom(newPos) - player.getHitbox().top(newPos));
        }
    }
    newPos.y += moveY;

    player.setPosition(newPos);
    // tu peux ajouter ici d'autres systèmes (collisions, IA, etc.)
}

void Game::render() {
    window.clear();
    window.setView(view);

    window.draw(mapper.vmap(tileMap));
    for (const auto& opp : opponents) {
        window.draw(mapper.vmap(opp.getShape(), opp.getPosition(), opp.getColor()));
        //window.draw(mapper.vmap(opp.getHitbox().getShape(), opp.getHitbox().getTransform()->getPosition(), sf::Color::White));
    }
    window.draw(mapper.vmap(player.getShape(), player.getPosition(), player.getColor()));
    //window.draw(mapper.vmap( player.getHitbox().getShape(), player.getHitbox().getTransform()->getPosition(), sf::Color::Magenta));

    window.display();
}
