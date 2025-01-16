#pragma once

#include <unordered_map>
#include <vector>
#include <variant>
#include <functional>
#include <SDL2/SDL.h>

#include "input/inputMapping.hpp"

class EventManager {
public:
    enum EventType {
        QUIT = SDL_QUIT,
        KEY_DOWN = SDL_KEYDOWN,
        KEY_UP = SDL_KEYUP
    };
private: 
    using callback_t = std::function<void(const SDL_Event&)>;
public:
    void addListener(EventType type, callback_t callback);
    void handleEvents();
private:


    SDL_Event event; ///< SDL_Event for handling events.

    void NotifyAll();

    std::unordered_map<EventType, std::vector<callback_t>> eventListeners;
};