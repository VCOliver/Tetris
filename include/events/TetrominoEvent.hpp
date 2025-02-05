#pragma once

#include "pch.h"
#include "core/base.hpp"

#include "event.hpp"

constexpr Uint32 TETROMINO_EVENT = REGISTER_SDL_EVENT(2);
static_assert(TETROMINO_EVENT < SDL_LASTEVENT, "COLLISION_EVENT exceeds SDL_LASTEVENT");

class TetrominoEvent : public Event {
public:

    TetrominoEvent() = default;

    EVENT_CLASS_CATEGORY(TetrominoCategory)
};

class TetrominoDropedEvent : public TetrominoEvent {
public:
    TetrominoDropedEvent() = default;

    EVENT_CLASS_TYPE(TetrominoDroped)
};