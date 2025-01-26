#include "input/inputManager.hpp"

InputManager::InputManager(std::unique_ptr<InputMapping> mapping)
    : inputMapping(std::move(mapping)) {}

void InputManager::onEvent(KeyEvent* e){
    if (e->GetEventType() == EventType::KeyPressed){
        auto key = static_cast<KeyPressedEvent*>(e)->getKey();
        handleInput(key, EventType::KeyPressed);
    }
    else if (e->GetEventType() == EventType::KeyReleased){
        auto key = static_cast<KeyReleasedEvent*>(e)->getKey();
        handleInput(key, EventType::KeyReleased);
    }
}

using command_ptr = InputMapping::command_ptr;

void InputManager::handleInput(KeyEvent::Key key, EventType type){
    if(inputMapping->getCommand(key.keycode)){
        if(type == EventType::KeyPressed){
            setKeyState(key.keycode, KeyState::PRESSED);
            std::cout << "Key pressed event: " << key.keycode << " (repeat = " << key.isRepeat << ")" << std::endl;
        }
        else if(type == EventType::KeyReleased){
            setKeyState(key.keycode, KeyState::RELEASED);
            std::cout << "Key released event: " << key.keycode << std::endl;
        }
    }
}

void InputManager::setKeyState(KeyCode key, KeyState state){
    keyState_map[key] = state;
}

bool InputManager::isKeyPressed(KeyCode key) const {
    auto it = keyState_map.find(key);
    return it != keyState_map.end() && it->second;
} 