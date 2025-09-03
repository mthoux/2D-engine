#include "../src/Engine/Model/Components/Vec2f.hpp"
#include "catch2/catch_all.hpp"

TEST_CASE("Test vecteur") {
    Vec2f v1 = {2,3};
    Vec2f v2 = {4,5};
    Vec2f v3 = {6,8};

    REQUIRE(v1+v2==v3);
}