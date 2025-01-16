#include "input/inputMapping.hpp"

InputMapping::InputMapping(){
    command_map = {
        {SDLK_s, std::make_shared<Command>()}
    };
}

void InputMapping::bindKey(SDL_KeyCode key, command_ptr command){
    command_map[key] = command;
}

InputMapping::command_ptr InputMapping::getCommand(SDL_KeyCode key) const {
    auto it = command_map.find(key); // Use find to locate the key
    if (it != command_map.end()) {
        return it->second; // Access the value via the iterator
    }
    return nullptr; // Return nullptr if the key is not found
}