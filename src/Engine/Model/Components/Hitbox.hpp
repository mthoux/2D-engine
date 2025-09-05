#pragma once
#include "../Geometry/Shape.hpp"
#include "../Math/Vec2f.hpp"

class Hitbox {
public:
    Hitbox(const Shape& shape, const Vec2f& offset = {0.f, 0.f})
        : shape(shape), localOffset(offset) {}

    // Teste la collision avec une autre hitbox
    // On passe les positions actuelles des deux objets
    bool intersects(const Vec2f& pos, const Hitbox& other, const Vec2f& otherPos) const;

    const Shape& getShape() const { return shape; }
    const Vec2f& getOffset() const { return localOffset; }

private:
    Shape shape;       // Forme locale
    Vec2f localOffset; // Offset de la forme dans le monde
};
