#pragma once

#include "entities/tetrominos.hpp"

class ICommands {
public:
    virtual ~ICommands() = default;
    virtual void getNewPiece(Tetrominos& tetro) = 0;
    virtual void execute() = 0;
};

using Command = ICommands*;

class DownCommand : public ICommands{
private:
    Tetrominos& tetro;
public:
    void getNewPiece(Tetrominos& tetro) override;

    void execute() override;
};