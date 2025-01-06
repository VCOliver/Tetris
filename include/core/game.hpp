#pragma once

#include <SDL2/SDL.h>

#define STD_WIDTH 800
#define STD_HEIGHT 600

class Game {
    int width, height;

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;

public:
    Game(int w, int h);
    void init();
    void run();
    void close();
};