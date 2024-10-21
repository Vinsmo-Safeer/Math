#ifndef MATH_UTILS_H
#define MATH_UTILS_H

#include "SDL.h"

namespace utils {
    inline float hireTimeInSeconds() {
        float t = SDL_GetTicks();
        t *= 0.001f;

        return t;
    }
}
#endif //MATH_UTILS_H
