#pragma once
#include "../Core/Transform.hpp"
#include "../Core/Math/Vec2f.hpp"
#include "../Core/Geometry/Shape.hpp"

#define DEFAULT_SIZE {100,100}

class WorldObject {
private:
    Transform transform;
    Shape shape;

public:
    // Constructeur
    WorldObject(const Shape& shape = Shape(), const Transform& transform = Transform())
        : transform(transform), shape(shape) {}
    WorldObject(const Shape& shape = Shape(), const Vec2f& pos = {0.f, 0.f}, const Vec2f& scale = DEFAULT_SIZE, const float& rot = 0)
        : transform(pos, rot, scale), shape(shape) {}

    // --- Getters ---
    const Vec2f& getPosition() const { return transform.getPosition(); }
    float getRotation() const { return transform.getRotation(); }
    const Vec2f& getScale() const { return transform.getScale(); }
    const Transform& getTransform() const { return transform; }
    Transform& getTransform() { return transform; }
    const Shape& getShape() const { return shape; }

    // --- Setters ---
    void setPosition(const Vec2f& pos) { transform.setPosition(pos); }
    void setRotation(float rot) { transform.setRotation(rot); }
    void setScale(const Vec2f& sc) { transform.setScale(sc); }

    // --- Helpers pour déplacer l'objet ---
    void translate(const Vec2f& delta) { transform.translate(delta); }
    void rotate(float deltaAngle) { transform.rotate(deltaAngle); }
    void rescale(const Vec2f& factor) { transform.rescale(factor); }
};
