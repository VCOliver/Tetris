#pragma once

#include <SDL2/SDL.h>

#include "inputMapping.hpp"

class InputManager {
private:
    std::unique_ptr<InputMapping> inputMapping;

    void handleKeydown(SDL_Keycode key);
    void handleKeyup(SDL_Keycode key);

public:

    explicit InputManager(std::unique_ptr<InputMapping> mapping);

    void handleInput(SDL_Event e);
};