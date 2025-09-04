#include "../src/Engine/Model/Geometry/Shape.hpp"
#include "../src/Engine/Model/Geometry/RectangleShape.hpp"
#include "../src/Engine/Model/Components/Hitbox.hpp"
#include "catch2/catch_all.hpp"


RectangleShape s({1,1}, {0,0});
RectangleShape s2({1,1}, {0,0});
Hitbox h1(s);
Hitbox h2(s2);

TEST_CASE("Test intersection") {
    //SECTION("T1") REQUIRE_FALSE(h1.intersects(s2));
}