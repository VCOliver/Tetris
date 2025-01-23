#pragma once

#include "entities/tetrominos.hpp"

class ICommands {
public:
    virtual ~ICommands() = default;
    virtual void getNewPiece(Tetrominos& tetro) = 0;
    virtual void execute() = 0;
};