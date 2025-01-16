#pragma once

#include <SDL2/SDL.h>

#include "inputMapping.hpp"

class InputManager {
private:
    std::unique_ptr<InputMapping> inputMapping;

public:

    explicit InputManager(std::unique_ptr<InputMapping> mapping);

    void handleInput(SDL_KeyCode key);
};