#include "input/inputManager.hpp"

InputManager::InputManager(std::unique_ptr<InputMapping> mapping)
    : inputMapping(std::move(mapping)) {}

using command_ptr = InputMapping::command_ptr;

void InputManager::handleInput(SDL_Event e){
    auto type = e.type;
    auto key = e.key.keysym.sym;
    if(type == SDL_KEYDOWN){
        handleKeydown(key);
    }
    command_ptr command = inputMapping->getCommand(key);
    if(command){
        command->execute();
    }
}