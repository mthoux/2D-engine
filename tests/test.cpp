#include "../src/Engine/Model/Core/Math/Vec2f.hpp"
#include "../src/Engine/Model/Core/Geometry/RectangleShape.hpp"
#include "../src/Engine/Model/Core/Hitbox.hpp"
#include "../src/Engine/Model/Objects/Entity.hpp"
#include "catch2/catch_all.hpp"
#include "../src/Engine/Model/Core/Geometry/RectangleShape.hpp"
#include "../src/Engine/Model/Core/Transform.hpp"
#include <iostream>

Entity e1({0,0}, RectangleShape({10,10}));
Entity e2({10,100}, RectangleShape({10,10}));

TEST_CASE("Test vecteur") {
    Vec2f v1 = {2,3};
    Vec2f v2 = {4,5};
    Vec2f v3 = {6,8};

    REQUIRE(v1+v2==v3);
}

TEST_CASE("Test shape transform") {
  
}