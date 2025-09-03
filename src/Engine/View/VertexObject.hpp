#pragma once
#include <SFML/Graphics.hpp>

class VertexObject : public sf::Drawable {
public:
    sf::VertexArray vertices;
private: 
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
        target.draw(vertices, states);
    }
};