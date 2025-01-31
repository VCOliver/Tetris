#pragma once 

#include "pch.h"
#include "core/base.hpp"

#define BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

enum class EventType
{
    None = 0,
    WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
    AppUpdate,
    KeyPressed, KeyReleased, KeyTyped,
    MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled,
    TetrionLeftCollision, TetrionRightCollision, TetrionBottomCollision, TetrominoCollision,
    TetrominoSpawned, TetrominoDroped
};

enum EventCategory
{
    None = 0,
    ApplicationCategory    = BIT(0),
    InputCategory          = BIT(1),
    KeyboardCategory       = BIT(2),
    MouseCategory          = BIT(3),
    MouseButtonCategory    = BIT(4),
    WindowCategory         = BIT(5),
    CollisionCategory      = BIT(6),
    TetrominoCategory      = BIT(7)
};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
							   virtual EventType GetEventType() const override { return GetStaticType(); }\
							   virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category)  static int GetStaticCategoryFlags() { return category; } \
                                        virtual int GetCategoryFlags() const override { return GetStaticCategoryFlags(); }

class Event
{
public:
    virtual ~Event() = default;

    bool Handled = false;

    virtual EventType GetEventType() const = 0;
    virtual const char* GetName() const = 0;
    virtual int GetCategoryFlags() const = 0;
    virtual std::string ToString() const { return GetName(); }

    bool IsInCategory(EventCategory category)
    {
        return GetCategoryFlags() & static_cast<int>(category);
    }

};

std::unique_ptr<Event> TranslateSDLEvent(const SDL_Event& sdlEvent);