#pragma once

#include <SDL2/SDL.h>

#include "systems/renderSystem.hpp"

class Game {
    int width, height;

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;

    RenderSystem* renderSystem;

public:
    Game(int w, int h);
    void init();
    void run();
    void close();
};