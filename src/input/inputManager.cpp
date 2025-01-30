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
    auto command = inputMapping->getCommand(key.keycode);
    if(command){
        if(type == EventType::KeyPressed){
            command->execute();
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

