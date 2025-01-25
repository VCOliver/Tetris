#pragma once

#include "pch.h"
#include <SDL2/SDL_ttf.h>

#include "utils/colors.hpp"
#include "utils/position.hpp"

class FontSystem {
    static TTF_Font* font;
    static char* m_fontPath;
    static int m_size;

public:
    static bool Init(const char*& fontPath, int size = 20);
    static void Shutdown();

    static bool setFontSize(int size);
    static bool loadFont();
    static bool loadFont(const char*& fontPath);
    static SDL_Surface* createSurface(const std::string& text, Color color);
    static void renderText(SDL_Renderer* renderer, const std::string& text, SDL_Point pos, Color color);
    static void renderText(SDL_Renderer* renderer, SDL_Surface* surface, SDL_Point pos, bool destroySurface=false);
};