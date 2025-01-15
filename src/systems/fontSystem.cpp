#include <iostream>

#include "systems/fontSystem.hpp"

FontSystem::FontSystem(int size) : font(nullptr), size(size) {
    if (TTF_Init() == -1) {
        std::cerr << "Failed to initialize SDL_ttf: " << TTF_GetError() << "\n";
    }
}

FontSystem::~FontSystem() {
    if (font) {
        TTF_CloseFont(font);
    }
    TTF_Quit();
}

void FontSystem::setFontSize(int size) {
    if (this->size != size) {
        this->size = size;
        if (font) {
            TTF_CloseFont(font);
        }
        font = TTF_OpenFont(fontPath.c_str(), size);
        if (!font) {
            std::cerr << "Failed to reload font: " << TTF_GetError() << "\n";
        }
    }
}

bool FontSystem::loadFont() {
    font = TTF_OpenFont(fontPath.c_str(), size);
    if (!font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << "\n";
        return false;
    }
    return true;
}

SDL_Surface* FontSystem::createSurface(const std::string& text, Color color){
    if (!font) {
        std::cerr << "Font not initialized!\n";
        return nullptr;
    }

    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color.toSDL_Color());
    if (!surface) {
        std::cerr << "Failed to render text: " << TTF_GetError() << "\n";
        return nullptr;
    }

    return surface;
}

void FontSystem::renderText(SDL_Renderer* renderer, const std::string& text, SDL_Point pos, Color color) const {
    if (!font) {
        std::cerr << "Font not initialized!\n";
        return;
    }

    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color.toSDL_Color());
    if (!surface) {
        std::cerr << "Failed to render text: " << TTF_GetError() << "\n";
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (!texture) {
        std::cerr << "Failed to create texture: " << SDL_GetError() << "\n";
        return;
    }

    SDL_Rect dst = {pos.x, pos.y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, nullptr, &dst);
    SDL_DestroyTexture(texture);
}

void FontSystem::renderText(SDL_Renderer* renderer, SDL_Surface* surface, SDL_Point pos, bool destroySurface) const {
    if (!surface) {
        std::cerr << "No surface param passed: " << TTF_GetError() << "\n";
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if(destroySurface) SDL_FreeSurface(surface);

    if (!texture) {
        std::cerr << "Failed to create texture: " << SDL_GetError() << "\n";
        return;
    }

    SDL_Rect dst = {pos.x, pos.y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, nullptr, &dst);
    SDL_DestroyTexture(texture);
}
