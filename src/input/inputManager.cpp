#include "input/inputManager.hpp"

#include "events/eventDispatcher.hpp"

InputManager::InputManager(std::unique_ptr<InputMapping> mapping)
    : inputMapping(std::move(mapping)) {}

void InputManager::onEvent(KeyEvent& e){
    EventDispatcher dispatcher(e);

    dispatcher.notify<KeyPressedEvent>([this](KeyPressedEvent& e){

        handleInput(e.key, EventType::KeyPressed);
        return true;
    });

    dispatcher.notify<KeyReleasedEvent>([this](KeyReleasedEvent& e){
        handleInput(e.key, EventType::KeyReleased);
        return true;
    });
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