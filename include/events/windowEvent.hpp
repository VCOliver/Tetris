#pragma once

#include "event.hpp"

class WindowCloseEvent : public Event
{
public:
    WindowCloseEvent() = default;

    EVENT_CLASS_TYPE(WindowClose)
    EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

class WindowResizeEvent : public Event {
    unsigned int width, height;
public:
    WindowResizeEvent(unsigned int width, unsigned int height)
        : width(width), height(height) {}

    unsigned int getWidth() const {return width;}
    unsigned int getHeight() const {return height;}

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "WindowResizeEvent: " << width << ", " << height;
        return ss.str();
    }

    EVENT_CLASS_TYPE(WindowResize)
    EVENT_CLASS_CATEGORY(EventCategoryApplication)
};