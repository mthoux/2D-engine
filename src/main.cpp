#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Window/Event.hpp>

#include "Engine/Model/Entities/Tile.hpp"
#include "Engine/Model/Entities/TileMap.hpp"
#include "Engine/View/Mapper.hpp"
#include "Utils/MapGenerator.hpp"
#include "Engine/Model/Entities/Entity.hpp"
#include "Engine/Controller/EntityController.hpp"
#include "Engine/Configurations.hpp"
#include "Engine/Model/Components/Vec2f.hpp"

int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Tilemap", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);
    sf::View view(sf::Vector2f(WINDOW_HEIGHT/2, WINDOW_WIDTH/2), sf::Vector2f(window.getSize().x, window.getSize().y));

    int width = WINDOW_WIDTH / TILE_SIZE;
    int height = WINDOW_HEIGHT / TILE_SIZE;
    std::vector<std::vector<int>> level2 = generateMap(width, height);

    TileMap tileMap({TILE_SIZE, TILE_SIZE}, level2, {float(height), float(width)});
    Mapper mapper;
    sf::VertexArray tileVO = mapper.vmap(tileMap);
    Entity player({0,0}, {TILE_SIZE,TILE_SIZE}, sf::Color::Red);
    Entity opponent({TILE_SIZE*2,TILE_SIZE}, {TILE_SIZE,TILE_SIZE}, sf::Color::Yellow);
    EntityController controller(tileMap, false);

    // run the main loop
    while (window.isOpen())
    {
        // handle events
        while (const std::optional event = window.pollEvent())
        {
            controller.handleInput(player);

            if (event->is<sf::Event::Closed>())
                window.close();

            if (auto wheelEvent = event->getIf<sf::Event::MouseWheelScrolled>())
            {
                float delta = wheelEvent->delta;

                delta = -delta;

                float zoomFactor = 1.0f + delta * 0.1f;

                if (zoomFactor > 0.0f)
                    view.zoom(zoomFactor);
            }

        }

        // draw the map
        window.clear();
        window.draw(tileVO);
        window.draw(mapper.vmap(player));
        window.draw(mapper.vmap(opponent));
        window.setView(view);
        window.display();
    }

    return 0;
}