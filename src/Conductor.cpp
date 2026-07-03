#include "Conductor.hpp"
#include "Engine/Model/Utils/MapGenerator.hpp"
#include "Engine/Model/Physics/CollisionSystem.hpp"
#include "Engine/Model/Utils/Utils.hpp"
#include "Engine/Model/Utils/Levels.hpp"
#include <iostream>
#include <cstdlib>  // rand, srand

// Fenêtre
constexpr int WINDOW_WIDTH = 512;
constexpr int WINDOW_HEIGHT = 512;
constexpr float MAP_WIDTH = 2000.f;
constexpr float MAP_HEIGHT = 2000.f;

// Tuiles
constexpr int TILE_SIZE = 64;

// Zoom (Facteurs)
constexpr float ZOOM_MIN = 0.3f;   // Zoom arrière maximum
constexpr float ZOOM_MAX = 3.0f;   // Zoom avant maximum
constexpr float ZOOM_SPEED = 0.1f; // Vitesse de zoom par cran de molette


// Vitesse de déplacement joueur (exemple)
constexpr float PLAYER_VELOCITY_STEP = 50.f;

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
    // opponents.emplace_back(Entity(RectangleShape(),Transform({TILE_SIZE*2, TILE_SIZE*3},0,{TILE_SIZE, TILE_SIZE}), sf::Color::Yellow, 0.f));
    // opponents.emplace_back(Entity(RectangleShape(),Transform({TILE_SIZE*4, TILE_SIZE*2},92,{TILE_SIZE*2, TILE_SIZE}), sf::Color::Cyan, 0.f));
    // opponents.emplace_back(Entity(RectangleShape(),Transform({TILE_SIZE*6, TILE_SIZE*6},0,{TILE_SIZE/3, TILE_SIZE/3}), sf::Color::Magenta, 0.f));
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

        // --- Gestion du Panning ---
        if (auto mouseBtn = event->getIf<sf::Event::MouseButtonPressed>()) {
            if (mouseBtn->button == sf::Mouse::Button::Left) {
                isPanning = true;
                // On utilise mapPixelToCoords pour avoir la position dans le monde
                lastMousePos = window.mapPixelToCoords(mouseBtn->position);
            }
        }

        if (auto mouseBtn = event->getIf<sf::Event::MouseButtonReleased>()) {
            if (mouseBtn->button == sf::Mouse::Button::Left) {
                isPanning = false;
            }
        }

        if (auto mouseMove = event->getIf<sf::Event::MouseMoved>()) {
            if (isPanning) {
                // 1. Calculer la position actuelle de la souris avec la vue actuelle
                sf::Vector2f currentMousePos = window.mapPixelToCoords(mouseMove->position);
                
                // 2. Calculer le delta
                sf::Vector2f delta = lastMousePos - currentMousePos;
                
                // 3. Déplacer la vue
                view.move(delta);
                //clampView();
                
                // 4. IMPORTANT : On met à jour lastMousePos, MAIS en se basant sur 
                // la nouvelle vue, on doit compenser le delta pour que le 
                // prochain calcul soit basé sur le même point dans le monde.
                // OU, plus simplement, on utilise la position brute du clic 
                // mais c'est complexe.
                
                // SOLUTION LA PLUS STABLE :
                // On met à jour lastMousePos en ajoutant le delta au "nouveau" point.
                lastMousePos = currentMousePos + delta;
            }
        }
        // --- Fin du Panning ---

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
            player.setVelocity(player.getVelocity() + 50);
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
            player.setVelocity(player.getVelocity() - 50);
        }

        if(event->is<sf::Event::Closed>())
            window.close();

        if(auto wheelEvent = event->getIf<sf::Event::MouseWheelScrolled>()) {
            float delta = -wheelEvent->delta; 
            float zoomFactor = 1.0f + delta * ZOOM_SPEED;
            
            if (zoomFactor > 0.0f) {
                // 1. Position du curseur dans le monde AVANT le zoom
                // On force la vue actuelle dans la fenêtre pour être sûr du calcul
                window.setView(view);
                sf::Vector2f mousePosBefore = window.mapPixelToCoords(wheelEvent->position);
                
                // 2. Application du zoom
                view.zoom(zoomFactor);
                
                // 3. Application des limites de taille (Min/Max)
                float minSize = WINDOW_WIDTH * ZOOM_MIN;
                float maxSize = WINDOW_WIDTH * ZOOM_MAX;
                
                sf::Vector2f newSize = view.getSize();
                if (newSize.x < minSize) newSize = {minSize, minSize};
                if (newSize.x > maxSize) newSize = {maxSize, maxSize};
                view.setSize(newSize);
                
                // 4. On remet la vue zoomée dans la fenêtre pour calculer la nouvelle position
                window.setView(view);
                sf::Vector2f mousePosAfter = window.mapPixelToCoords(wheelEvent->position);
                
                // 5. Décalage pour "ancrer" le point sous le curseur
                view.move(mousePosBefore - mousePosAfter);
                
                // 6. On applique les limites de panning (la carte)
                //clampView();
                
                // 7. Update final de la vue
                window.setView(view);
            }
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

void Conductor::clampView() {
    sf::Vector2f viewSize = view.getSize();
    sf::Vector2f viewCenter = view.getCenter();

    // Calcul des limites du rectangle de vue
    float minX = viewSize.x / 2.f;
    float maxX = MAP_WIDTH - (viewSize.x / 2.f);
    float minY = viewSize.y / 2.f;
    float maxY = MAP_HEIGHT - (viewSize.y / 2.f);

    // On force le centre de la vue à rester dans ces limites
    viewCenter.x = std::clamp(viewCenter.x, minX, maxX);
    viewCenter.y = std::clamp(viewCenter.y, minY, maxY);

    view.setCenter(viewCenter);
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
