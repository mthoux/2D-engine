#include "../src/Engine/Model/Components/Shape.hpp"
#include "../src/Engine/Model/Components/RectangleShape.hpp"
#include "../src/Engine/Model/Components/Hitbox.hpp"
#include "catch2/catch_all.hpp"


RectangleShape s({0,0}, {1,1}, {0,0});
RectangleShape s2({4,4}, {1,1}, {0,0});
Hitbox h1(s);
Hitbox h2(s2);

TEST_CASE("Test intersection") {
    SECTION("T1") REQUIRE_FALSE(h1.intersects(s2));
}