#pragma once 

#include "pch.h"

#include "utils/position.hpp"
#include "events/event.hpp"

class Window {
    SDL_Window* window; ///< Pointer to the SDL_Window.
    std::string title;
    unsigned int width;
    unsigned int height;

public:
    using EventCallback = std::function<void()>;
    
    Window(const std::string& title, unsigned int width, unsigned int height);
    ~Window();

    inline SDL_Window* getSDL_Window() const {return window;}
    
    inline void onUpdate(){}
    unsigned int getHeight() const;
    unsigned int getWidth() const;
    const Position getWindowCenter();
    void setEventCallback(const EventCallback& callback);
private:
    void shutdown();

    struct WindowData {
        std::string title;
        unsigned int width, height;
        EventCallback eventCallback;
    };

    WindowData data;

};