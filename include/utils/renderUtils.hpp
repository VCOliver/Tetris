#pragma once

#include <SDL2/SDL.h>

#include "utils/position.hpp"
#include "components/renderComponents.hpp"

namespace render {
    const Position getWindowCenter(SDL_Window* window);
    void renderDrawTrapz(SDL_Renderer* renderer, Trapezium trapz);
    void renderFillTrapz(SDL_Renderer* renderer, Trapezium trapz);
}

namespace test {
    float lerp(float a, float b, float t);
    void drawHorizontalLine(SDL_Renderer* renderer, int x1, int x2, int y);
    void drawFilledTrapeziumScanline(SDL_Renderer* renderer, Trapezium* trapezium);
    
    void drawFilledTrapeziumPixel(SDL_Renderer* renderer, Trapezium* trapezium);
    int isPointInTrapezium(int px, int py, Trapezium* trapezium);
   int isPointInTriangle(int px, int py, int x1, int y1, int x2, int y2, int x3, int y3);
}