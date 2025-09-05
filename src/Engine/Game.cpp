#include "Game.hpp"
#include "../Utils/MapGenerator.hpp"
#include "Configurations.hpp"

Game::Game()
    : window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Tilemap")
    , view(sf::Vector2f(WINDOW_WIDTH/2.f, WINDOW_HEIGHT/2.f), sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT))
    , tileMap({TILE_SIZE, TILE_SIZE}, generateMap(WINDOW_WIDTH/TILE_SIZE, WINDOW_HEIGHT/TILE_SIZE), {float(WINDOW_HEIGHT / TILE_SIZE), float(WINDOW_WIDTH / TILE_SIZE)})
    , mapper()
    , player({0,0}, RectangleShape({TILE_SIZE, TILE_SIZE}), sf::Color::Red, 230.f)
    , opponent({TILE_SIZE*2, TILE_SIZE}, RectangleShape({TILE_SIZE, TILE_SIZE}), sf::Color::Yellow, 0.f)
    , controller(tileMap, false)
{
    window.setFramerateLimit(60);
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
    controller.handleInput(player, dt);
    // tu peux ajouter ici d'autres systèmes (collisions, IA, etc.)
}

void Game::render() {
    window.clear();
    window.setView(view);

    window.draw(mapper.vmap(tileMap));
    window.draw(mapper.vmap(player.getShape(), player.getPosition(), player.getColor()));
    window.draw(mapper.vmap(opponent.getShape(), opponent.getPosition(), opponent.getColor()));
    //window.draw(mapper.vmap(player.getHitbox().getShape(), sf::Color::Magenta));

    window.display();
}
