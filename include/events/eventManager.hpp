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
        QUIT,
        KEY_DOWN,
        KEY_UP
    };

private:

    using quit_handler = std::function<void(void)>;
    using keyboard_handler = std::function<void(Input)>;
    using callback_t = std::variant<quit_handler, keyboard_handler>;


    SDL_Event event; ///< SDL_Event for handling events.

    void handleEvents();
    void addListener(EventType type, callback_t callback);

    std::unordered_map<EventType, std::vector<callback_t>> eventListeners;
};