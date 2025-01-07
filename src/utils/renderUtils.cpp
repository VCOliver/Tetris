#include <algorithm>

#include "utils/renderUtils.hpp"
#include "utils/mathUtils.hpp"

const Position render::getWindowCenter(SDL_Window* window){
    int w;
    int h;
    SDL_GetWindowSize(window, &w, &h);
    w /= 2;
    h /= 2;
    // w -= (STD_BLOCK_W/2);
    // h -= (STD_BLOCK_H/2);
    w /= STD_BLOCK_W;
    h /= STD_BLOCK_H;
    return {w, h};
}

void render::renderFillTrapz(SDL_Renderer* renderer, Trapezium trapz) {
    float d1 = math::calculateDistace(trapz.top_left, trapz.top_right);
}

void render::renderDrawTrapz(SDL_Renderer* renderer, Trapezium trapz){
    SDL_RenderDrawLine(renderer, trapz.top_left.x, trapz.top_left.y, trapz.top_right.x, trapz.top_right.y);
    SDL_RenderDrawLine(renderer, trapz.top_right.x, trapz.top_right.y, trapz.bottom_right.x, trapz.bottom_right.y);
    SDL_RenderDrawLine(renderer, trapz.bottom_right.x, trapz.bottom_right.y, trapz.bottom_left.x, trapz.bottom_left.y);
    SDL_RenderDrawLine(renderer, trapz.bottom_left.x, trapz.bottom_left.y, trapz.top_left.x, trapz.top_left.y);
}
