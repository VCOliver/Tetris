#pragma once

#include <SDL2/SDL.h>

#include "utils/position.hpp"
#include "components/renderComponents.hpp"

struct Triangle {
    SDL_Point v1;
    SDL_Point v2;
    SDL_Point v3;
};

namespace render {
    const Position getWindowCenter(SDL_Window* window);
    void renderDrawTrapz(SDL_Renderer* renderer, Trapezium trapz);
    void renderFillTrapz(SDL_Renderer* renderer, const Trapezium& trapezium);
    int isPointInTrapezium(int px, int py, const Trapezium& trapezium);
    int isPointInTriangle(SDL_Point p, Triangle& tri);
}