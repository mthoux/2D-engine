#pragma once
#include <vector>
#include "Vec2f.hpp"
#include "Shape.hpp"

class RectangleShape : public Shape {
public:
    // Constructeur avec position, taille et couleur
    RectangleShape(const Vec2f& position, const Vec2f& size, const sf::Color& color = sf::Color::White);

    // Getter/Setter taille
    Vec2f getSize() const;
    void setSize(const Vec2f& newSize);

private:
    Vec2f size;
    void updateVertices(); // recalcul des 4 sommets
};

