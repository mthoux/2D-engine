#pragma once

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
};
