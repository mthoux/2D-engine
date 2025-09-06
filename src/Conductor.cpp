#include "Conductor.hpp"
#include "Engine/Model/Utils/MapGenerator.hpp"
#include <iostream>

#define WINDOW_WIDTH    512
#define WINDOW_HEIGHT   512
#define TILE_SIZE       64

Conductor::Conductor()
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

void Conductor::run() {
    sf::Clock clock;
    while(window.isOpen()) {
        float dt = clock.restart().asSeconds();

        processEvents();
        update(dt);
        render();
    }
}

void Conductor::processEvents() {
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

void Conductor::update(float dt) {
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

void Conductor::render() {
    
    window.clear();
    window.setView(view);

    window.draw(mapper.vmap(tileMap));
    for (const auto& opp : opponents) {
        window.draw(mapper.vmap(opp.getShape(), opp.getPosition(), opp.getColor()));
    }
    window.draw(mapper.vmap(player.getShape(), player.getPosition(), player.getColor()));

    window.display();
}
