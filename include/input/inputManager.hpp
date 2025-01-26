#pragma once

#include "pch.h"

#include "core/base.hpp"
#include "events/keyEvent.hpp"
#include "inputMapping.hpp"

class InputManager {
public:
    enum KeyState {
        PRESSED,
        RELEASED
    };

    explicit InputManager(std::unique_ptr<InputMapping> mapping);

    void onEvent(KeyEvent* e);
    void handleInput(KeyEvent::Key key, EventType type);

private:

    std::unique_ptr<InputMapping> inputMapping;
    std::unordered_map<KeyCode, KeyState>  keyState_map;

    void setKeyState(KeyCode key, KeyState state);
    bool isKeyPressed(KeyCode key) const;
};