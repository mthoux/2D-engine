#include "Conductor.hpp"
#include "Engine/Model/Utils/MapGenerator.hpp"
#include "Engine/Model/Physics/CollisionSystem.hpp"
#include "Engine/Model/Utils/Utils.hpp"
#include "Engine/Model/Utils/Levels.hpp"
#include <iostream>
#include <cstdlib>  // rand, srand

#define WINDOW_WIDTH    512
#define WINDOW_HEIGHT   512
#define TILE_SIZE       64

Conductor::Conductor()
    : window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Tilemap")
    , view(sf::Vector2f(WINDOW_WIDTH/2.f, WINDOW_HEIGHT/2.f), sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT))
    , tileMap({TILE_SIZE, TILE_SIZE}, LEVEL1, {float(WINDOW_HEIGHT / TILE_SIZE), float(WINDOW_WIDTH / TILE_SIZE)})
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
        render(dt);
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

RectangleShape getCollisionBox(Entity& entity, float dt) {
    Shape realShape = applyTransform(entity.getShape(), entity.getTransform());
    float vdt = float(entity.getVelocity()*dt);
    Vec2f leftPoint = realShape.getExtreme(Direction::Left) - Vec2f{vdt, 0}*2;
    Vec2f topPoint = realShape.getExtreme(Direction::Top) - Vec2f{0, vdt}*2;
    Vec2f rightPoint = realShape.getExtreme(Direction::Right) + Vec2f{vdt, 0}*2;
    Vec2f bottomPoint = realShape.getExtreme(Direction::Bottom) + Vec2f{0, vdt}*2;
    return RectangleShape({leftPoint.x, bottomPoint.y}, {rightPoint.x, topPoint.y});
}

void Conductor::update(float dt) {

    Vec2f oldPos = player.getPosition();
    Vec2f delta = controller.handleInput(player, dt);
    Vec2f newPos = oldPos + delta;

    player.setPosition(newPos);
    Shape playerShape = applyTransform(player.getShape(), player.getTransform());

    RectangleShape collisionBox = getCollisionBox(player, dt);
    std::vector<Shape> collisionToTest;
    for(Entity& opp : opponents) {
        Shape s = applyTransform(opp.getShape(), opp.getTransform());
        if (collisionBox.contains(s.getReference())) {
            collisionToTest.push_back(s);
            std::cout << "TRUE" << std::endl;
        } else std::cout << "CACA" << std::endl;
    }

    for(Shape s : collisionToTest) {
        std::optional<Vec2f> mtv = CollisionSystem2::getMTV(playerShape, s);

        if (mtv) {
            // Déplacer le joueur hors de la collision
            player.setPosition(player.getPosition() - *mtv);
        }
    }


    // Récupère la tuile correspondante
    // std::optional<Tile*> tile = tileMap.getTileAt(newPos);

    // if (tile && *tile && !(*tile)->isWalkable()) {
    //     newPos = oldPos; // bloqué
    // }
}


void Conductor::render(float dt) {
    
    window.clear();
    window.setView(view);

    window.draw(mapper.vmap(tileMap));
    for (const auto& opp : opponents) {
        window.draw(mapper.vmap(opp.getShape(), opp.getTransform(), opp.getColor()));
    }
    Shape s = getCollisionBox(player, dt);
    window.draw(mapper.vmap(s));

    window.draw(mapper.vmap(player.getShape(), player.getTransform(), player.getColor()));

    window.display();
}
