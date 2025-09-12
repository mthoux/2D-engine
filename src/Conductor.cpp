#include "Conductor.hpp"
#include "Engine/Model/Utils/MapGenerator.hpp"
#include "Engine/Model/Physics/CollisionSystem.hpp"
#include "Engine/Model/Physics/CollisionSystem2.hpp"
#include "Engine/Model/Utils/Utils.hpp"
#include <iostream>
#include <cstdlib>  // rand, srand

#define WINDOW_WIDTH    512
#define WINDOW_HEIGHT   512
#define TILE_SIZE       64

Conductor::Conductor()
    : window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Tilemap")
    , view(sf::Vector2f(WINDOW_WIDTH/2.f, WINDOW_HEIGHT/2.f), sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT))
    , tileMap({TILE_SIZE, TILE_SIZE}, generateMap(WINDOW_WIDTH/TILE_SIZE, WINDOW_HEIGHT/TILE_SIZE), {float(WINDOW_HEIGHT / TILE_SIZE), float(WINDOW_WIDTH / TILE_SIZE)})
    , mapper()
    , player(RectangleShape(), Transform({0,0},0,{TILE_SIZE, TILE_SIZE}), sf::Color::Red, 230.f)
    , controller(tileMap, false)
{
    window.setFramerateLimit(60);

    // On remplit le vector d'ennemis
    opponents.emplace_back(Entity(RectangleShape(),Transform({TILE_SIZE*2, TILE_SIZE*3},0,{TILE_SIZE, TILE_SIZE}), sf::Color::Yellow, 0.f));
    opponents.emplace_back(Entity(RectangleShape(),Transform({TILE_SIZE*4, TILE_SIZE*2},92,{TILE_SIZE*2, TILE_SIZE}), sf::Color::Cyan, 0.f));
    opponents.emplace_back(Entity(RectangleShape(),Transform({TILE_SIZE*6, TILE_SIZE*6},0,{TILE_SIZE/3, TILE_SIZE/3}), sf::Color::Magenta, 0.f));
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

    // Déplacement brut
    player.setPosition(oldPos + delta);

    // Transforme les shapes
    Shape playerShape = applyTransform(player.getShape(), player.getTransform());
    Shape oppShape = applyTransform(opponents[1].getShape(), opponents[1].getTransform());

    // Calcul du MTV
    std::optional<Vec2f> mtv = CollisionSystem2::getMTV(playerShape, oppShape);

    if (mtv) {
        // Déplacer le joueur hors de la collision
        player.setPosition(player.getPosition() - *mtv);
    }

    moveRandom(opponents[1], 100.f);
}

// Pour tester
void Conductor::moveRandom(Entity& e, float maxStep) {
    Vec2f oldPos = e.getPosition();
    // Génère un déplacement aléatoire entre -maxStep et +maxStep
    float dx = (static_cast<float>(rand()) / RAND_MAX) * 2.f * maxStep - maxStep;
    float dy = (static_cast<float>(rand()) / RAND_MAX) * 2.f * maxStep - maxStep;
    Vec2f delta = {dx, dy}; 
    e.setPosition(e.getPosition() + delta);

    std::vector<Entity> others;

    // Ajouter le player s'il n'est pas e
    if (&player != &e) {
        others.emplace_back(player);
    }

    // Ajouter tous les opponents sauf e
    for (auto& opp : opponents) {
        if (&opp != &e) {
            others.emplace_back(opp);
        }
    }

    for(Entity o : others) {
        if (CollisionSystem2::isOverlaping(applyTransform(e.getShape(), e.getTransform()), applyTransform(o.getShape(), e.getTransform())))
        e.setPosition(oldPos);
    }
}

void Conductor::render() {
    
    window.clear();
    window.setView(view);

    window.draw(mapper.vmap(tileMap));
    for (const auto& opp : opponents) {
        window.draw(mapper.vmap(opp.getShape(), opp.getTransform(), opp.getColor()));
    }
    window.draw(mapper.vmap(player.getShape(), player.getTransform(), player.getColor()));

    window.display();
}
