#pragma once

#include <SDL2/SDL.h>

#include "utils/position.hpp"
#include "components/renderComponents.hpp"

#define OPAQUE 255

namespace render {
    const Position getWindowCenter(SDL_Window* window);
    void renderDrawTrapz(SDL_Renderer* renderer, Trapezium trapz);
    void renderFillTrapz(SDL_Renderer* renderer, Trapezium trapz);
}