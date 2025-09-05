#pragma once
#include "../Geometry/Vec2f.hpp"

class Transform {
private:
    Vec2f position;
    float rotation;   // en radians
    Vec2f scale;

public:
    Transform(Vec2f pos = {0.f, 0.f}, float rot = 0.f, Vec2f sc = {1.f, 1.f})
        : position(pos), rotation(rot), scale(sc) {}

    // --- Getters ---
    const Vec2f& getPosition() const { return position; }
    float getRotation() const { return rotation; }
    const Vec2f& getScale() const { return scale; }

    // --- Setters ---
    void setPosition(const Vec2f& pos) { position = pos; }
    void setRotation(float rot) { rotation = rot; }
    void setScale(const Vec2f& sc) { scale = sc; }

    // --- Helpers ---
    void translate(const Vec2f& delta) { position += delta; }
    void rotate(float deltaAngle) { rotation += deltaAngle; }
    void rescale(const Vec2f& factor) {
        scale.x *= factor.x;
        scale.y *= factor.y;
    }
};
