#include "../src/Engine/Model/Geometry/Shape.hpp"
#include "../src/Engine/Model/Geometry/RectangleShape.hpp"
#include "../src/Engine/Model/Components/Hitbox.hpp"
#include "../src/Engine/Model/Components/Transform.hpp"
#include "catch2/catch_all.hpp"

const Transform pos({0,0}, 0, {0,0});
RectangleShape s({1,1}, {0,0});
RectangleShape s2({1,1}, {0,0});

TEST_CASE("Test intersection") {
    //SECTION("T1") REQUIRE(h1yo.intersects(h2yo));
}