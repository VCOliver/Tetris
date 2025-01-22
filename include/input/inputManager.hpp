#pragma once

#include "pch.h"

#include "inputMapping.hpp"

class InputManager {
public:
    enum KeyState {
        PRESSED,
        RELEASED
    };

    explicit InputManager(std::unique_ptr<InputMapping> mapping);

    void handleInput(SDL_Event e);

private:

    using KeyCode = SDL_Keycode;

    std::unique_ptr<InputMapping> inputMapping;
    std::unordered_map<KeyCode, KeyState>  keyState_map;

    void setKeyState(KeyCode key, KeyState state);
    bool isKeyPressed(KeyCode key) const;
};