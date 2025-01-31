#pragma once

#include "pch.h"

#include "event.hpp"
#include "entities/tetrion.hpp"
#include "entities/tetrominos.hpp"

constexpr Uint32 COLLISION_EVENT = SDL_USEREVENT + 1;
static_assert(COLLISION_EVENT < SDL_LASTEVENT, "COLLISION_EVENT exceeds SDL_LASTEVENT");

class CollisionEvent : public Event {
public:

    CollisionEvent() = default;

    EVENT_CLASS_CATEGORY(CollisionCategory)
};

class TetrionLeftCollisionEvent : public CollisionEvent {
public:
    TetrionLeftCollisionEvent() = default;

    EVENT_CLASS_TYPE(TetrionLeftCollision)
};

class TetrionRightCollisionEvent : public CollisionEvent {
public:
    TetrionRightCollisionEvent() = default;

    EVENT_CLASS_TYPE(TetrionRightCollision)
};

class TetrionBottomCollisionEvent : public CollisionEvent {
public:
    TetrionBottomCollisionEvent() = default;

    EVENT_CLASS_TYPE(TetrionBottomCollision)
};

class TetrominoCollisionEvent : public CollisionEvent {
public:
    TetrominoCollisionEvent() = default;

    EVENT_CLASS_TYPE(TetrominoCollision)
};

class CollisionChecker {
    Tetrominos& tetromino;
    Tetrion& tetrion;
public:
    CollisionChecker(Tetrominos& tetromino, Tetrion& tetrion) 
                    : tetromino(tetromino), tetrion(tetrion){};

    void setTarget(Tetrominos& tetromino){ this->tetromino = tetromino;}
    void checkCollision();
};