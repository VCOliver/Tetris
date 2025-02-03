#pragma once

#include "entities/tetrominos.hpp"
#include "core/log.hpp"

class ICommands {
public:
    virtual ~ICommands() = default;
    virtual void bindNewPiece(Tetrominos* tetro) = 0;
    virtual void execute() = 0;
};

class DownCommand : public ICommands {
    Tetrominos* current_tetro;
public:
    void bindNewPiece(Tetrominos* tetro) override {
        current_tetro = tetro;
    }

    void execute() override {
        LOG_INFO("Executing Down Command");
        current_tetro->move(Tetrominos::DOWN);
    }
};

class RightCommand : public ICommands {
    Tetrominos* current_tetro;
public:
    void bindNewPiece(Tetrominos* tetro) override {
        current_tetro = tetro;
    }

    void execute() override {
        LOG_INFO("Executing Right Command");
        current_tetro->move(Tetrominos::RIGHT);
    }
};

class LeftCommand : public ICommands {
    Tetrominos* current_tetro;
public:
    void bindNewPiece(Tetrominos* tetro) override {
        current_tetro = tetro;
    }

    void execute() override {   
        LOG_INFO("Executing Left Command");
        current_tetro->move(Tetrominos::LEFT);
    }
};

class RotateClockwiseCommand : public ICommands {
    Tetrominos* current_tetro;
public:
    void bindNewPiece(Tetrominos* tetro) override {
        current_tetro = tetro;
    }

    void execute() override {   
        LOG_INFO("Executing Rotate Clockwise Command");
        current_tetro->rotate(Tetrominos::ROTATE_CLOCKWISE);
    }
};

class RotateCounterClockwiseCommand : public ICommands {
    Tetrominos* current_tetro;
public:
    void bindNewPiece(Tetrominos* tetro) override {
        current_tetro = tetro;
    }

    void execute() override {   
        LOG_INFO("Executing Rotate Counter Clockwise Command");
        current_tetro->rotate(Tetrominos::ROTATE_COUNTERCLOCKWISE);
    }
};