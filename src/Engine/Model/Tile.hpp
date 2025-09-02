#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>

class Tile
{
public:
    enum Type { 
        NONE,
        GRASS, 
        WATER
    };
    Tile();
    Tile(Type type, sf::Vector2f position, sf::Vector2f size, sf::Color color = sf::Color::White);

    Type type;
    sf::Vector2f position;
    sf::Vector2f size;
    sf::Color color;
private:

};