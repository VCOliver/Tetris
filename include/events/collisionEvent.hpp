#pragma once

#include "pch.h"

#include "event.hpp"

constexpr Uint32 COLLISION_EVENT = SDL_USEREVENT + 1;
static_assert(COLLISION_EVENT < SDL_LASTEVENT, "COLLISION_EVENT exceeds SDL_LASTEVENT");

class CollisionEvent : public Event {
public:

    CollisionEvent() = default;

    EVENT_CLASS_CATEGORY(CollisionCategory)
};

class TetrionCollisionEvent : public CollisionEvent {
public:
    TetrionCollisionEvent() = default;

    EVENT_CLASS_TYPE(TetrionCollision)
};

class TetrominoCollisionEvent : public CollisionEvent {
public:
    TetrominoCollisionEvent() = default;

    EVENT_CLASS_TYPE(TetrominoCollision)
};

