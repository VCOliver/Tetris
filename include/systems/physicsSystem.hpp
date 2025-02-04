#pragma once

#include "pch.h"

#include "entities/tetrominos.hpp"

class PhysicsSystem {
    Tetrominos* activeTetromino;
    bool gravity_enabled = false;
    std::chrono::steady_clock::time_point lastUpdateTime;
    std::chrono::milliseconds gravityInterval = std::chrono::milliseconds(1000);
public:
    PhysicsSystem() : activeTetromino(nullptr) {
        lastUpdateTime = std::chrono::steady_clock::now();
    }

    void startGravity(){ gravity_enabled = true;}

    void stopGravity(){ gravity_enabled = false; }

    void setActiveTetromino(Tetrominos* tetromino) {
        activeTetromino = tetromino;
    }

    void setGravitySpeed(std::chrono::milliseconds interval) {
        gravityInterval = interval;
    }

    void update();

    std::chrono::milliseconds getGravitySpeed() const {
        return gravityInterval;
    }

    void onLevelUpEvent();
};