#pragma once

#include "pch.h"

#include "tetrion.hpp"
#include "tetrominos.hpp"
#include "systems/renderSystem.hpp"

class Playfield : public Renderable {
private:
    std::unique_ptr<Tetrion> tetrion;
    Tetrominos* tetromino;
    Position start_pos;

public:
    Playfield(Position pos);
    ~Playfield();

    void spawnTetromino();
    Tetrominos* getTetromino() const { return tetromino; }

    void onUpdate();

    void render() const;
};