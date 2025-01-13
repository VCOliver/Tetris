#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

#include "utils/colors.hpp"
#include "utils/position.hpp"

class FontSystem {
    TTF_Font* font;
    const std::string fontPath = "assets/fonts/PixelifySans-Regular.ttf";
    int size;

public:
    FontSystem(int size = 24);
    ~FontSystem();

    void setFontSize(int size);
    bool loadFont();
    void renderText(SDL_Renderer* renderer, const std::string& text, Position pos, Color color);
};