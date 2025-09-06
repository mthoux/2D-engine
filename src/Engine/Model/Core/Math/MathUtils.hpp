#pragma once
#include <cmath>

namespace MathUtils {

    inline float degToRad(float degrees) {
        return degrees * (static_cast<float>(M_PI) / 180.f);
    }

    inline float radToDeg(float radians) {
        return radians * (180.f / static_cast<float>(M_PI));
    }

    // tu peux ajouter d'autres helpers comme clamp, lerp, etc.
}
