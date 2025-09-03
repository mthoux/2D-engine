#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Window/Event.hpp>

#include "Engine/Model/Tile.hpp"
#include "Engine/Model/TileMap.hpp"
#include "Engine/View/Mapper.hpp"
#include "Utils/MapGenerator.hpp"
#include "Engine/View/VertexObject.hpp"
#include "Engine/Model/Entity.hpp"
#include "Engine/Controller/EntityController.hpp"
#include "Engine/Configurations.hpp"

int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Tilemap", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);
    sf::View view(sf::Vector2f(WINDOW_HEIGHT/2, WINDOW_WIDTH/2), sf::Vector2f(window.getSize().x, window.getSize().y));

    Mapper mapper;
    Entity player({TILE_SIZE,TILE_SIZE}, {TILE_SIZE,TILE_SIZE}, sf::Color::Red);
    EntityController controller;


    int width = WINDOW_WIDTH / TILE_SIZE;
    int height = WINDOW_HEIGHT / TILE_SIZE;
    std::vector<std::vector<int>> level2 = generateMap(width, height);

    TileMap tileMap({TILE_SIZE, TILE_SIZE}, level2, {float(height), float(width)});
    VertexObject tileVO = mapper.vmap(tileMap);

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
        window.setView(view);
        window.display();
    }

    return 0;
}