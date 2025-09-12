#pragma once
#include <cmath>

struct Vec2f {
    float x = 0.f;
    float y = 0.f;

    Vec2f() = default;
    Vec2f(float x, float y) : x(x), y(y) {}

    Vec2f operator+(const Vec2f& other) const { return {x + other.x, y + other.y}; }
    Vec2f operator-(const Vec2f& other) const { return {x - other.x, y - other.y}; }
    Vec2f operator*(float scalar) const { return {x * scalar, y * scalar}; }
    Vec2f operator/(float scalar) const { return {x / scalar, y / scalar}; }

    Vec2f& operator+=(const Vec2f& other) { x += other.x; y += other.y; return *this; }
    Vec2f& operator-=(const Vec2f& other) { x -= other.x; y -= other.y; return *this; }
    Vec2f& operator*=(float scalar) { x *= scalar; y *= scalar; return *this; }
    Vec2f& operator/=(float scalar) { x /= scalar; y /= scalar; return *this; }

    bool operator==(const Vec2f& other) const { return x == other.x && y == other.y; }
    bool operator!=(const Vec2f& other) const { return !(*this == other); }

    Vec2f operator-() const {return Vec2f(-x, -y); }

    // --- Fonctions utilitaires ---
    float dot(const Vec2f& other) const { return x * other.x + y * other.y; }
    float length() const { return std::sqrt(x * x + y * y); }
    Vec2f normalized() const {
        float len = length();
        return (len > 1e-6f) ? Vec2f(x / len, y / len) : Vec2f(0.f, 0.f);
    }
};
