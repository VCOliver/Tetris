#include "input/inputManager.hpp"

InputManager::InputManager(std::unique_ptr<InputMapping> mapping)
    : inputMapping(std::move(mapping)) {}

using command_ptr = InputMapping::command_ptr;

void InputManager::setKeyState(KeyCode key, KeyState state){
    keyState_map[key] = state;
}

bool InputManager::isKeyPressed(KeyCode key) const {
    auto it = keyState_map.find(key);
    return it != keyState_map.end() && it->second;
} 