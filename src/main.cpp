#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Window/Event.hpp>

#include "Engine/Model/Tile.hpp"
#include "Engine/Model/TileMap.hpp"
#include "Engine/View/Rendering.hpp"
#include "Utils/MapGenerator.hpp"

#define WINDOW_WIDTH    512
#define WINDOW_HEIGHT   512
#define TILE_SIZE       53

#define KEY_UP          Z
#define KEY_LEFT        Q
#define KEY_DOWN        S
#define KEY_RIGHT       D

int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Tilemap", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);

    sf::View view(sf::Vector2f(WINDOW_HEIGHT/2, WINDOW_WIDTH/2), sf::Vector2f(window.getSize().x, window.getSize().y));

    const std::vector<std::vector<int>> level = {
        {1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 1},
        {1, 0, 1, 1, 0, 2},
        {1, 0, 2, 0, 3, 1},
        {1, 0, 0, 2, 0, 1},
        {1, 1, 1, 1, 1, 2},
        {2, 2, 2, 2, 2, 2},
        {2, 0, 0, 0, 0, 2}
    };

    int width = WINDOW_WIDTH / TILE_SIZE;
    int height = WINDOW_HEIGHT / TILE_SIZE;
    std::vector<std::vector<int>> level2 = generateMap(width, height);

    TileMap tileMap({TILE_SIZE, TILE_SIZE}, level2, {float(height), float(width)});
    Tile tile(Tile::GRASS, {0,0}, {TILE_SIZE, TILE_SIZE}, sf::Color::Green);
    Tile tile2(Tile::GRASS, {199,23}, {TILE_SIZE, TILE_SIZE}, sf::Color::Yellow);
    sf::VertexArray tileVertices = renderTile(tile);
    sf::VertexArray tile2Vertices = renderTile(tile2);
    sf::VertexArray tileMapVertices = renderTileMap(tileMap);

    // run the main loop
    while (window.isOpen())
    {
        // handle events
        while (const std::optional event = window.pollEvent())
        {
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
        window.draw(tileVertices);
        window.draw(tileMapVertices);
        window.setView(view);
        window.display();
    }

    return 0;
}