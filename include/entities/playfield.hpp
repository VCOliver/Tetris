#pragma once

#include "pch.h"

#include "tetrion.hpp"
#include "tetrominos.hpp"
#include "systems/renderSystem.hpp"

class Playfield : public Renderable {
private:
    Tetrion* tetrion;
    Tetrominos* tetromino;
    Position start_pos;

public:
    Playfield(Position pos);
    ~Playfield();

    void render(SDL_Renderer* renderer) const;
};