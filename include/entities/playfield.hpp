#pragma once

#include <SDL2/SDL.h>

#include "tetrion.hpp"
#include "utils/renderUtils.hpp"

class Playfield : public Renderable {
private:
    Tetrion* tetrion;
    Position start_pos;

public:
    Playfield(Position pos);
    ~Playfield();

    void render(SDL_Renderer* renderer) const;
};