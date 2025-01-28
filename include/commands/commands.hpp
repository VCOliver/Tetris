#pragma once

#include "entities/tetrominos.hpp"

class ICommands {
public:
    virtual ~ICommands() = default;
    virtual void getNewPiece(Tetrominos& tetro) = 0;
    virtual void execute() = 0;
};

class DownCommand : public ICommands {
    Tetrominos* current_tetro;
public:
    void bindNewPiece(Tetrominos& tetro) override {
        current_tetro = &tetro;
    }

    void execute() override {
        current_tetro->move(Tetrominos::DOWN);
    }
};