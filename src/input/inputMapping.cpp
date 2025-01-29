#include "input/inputMapping.hpp"

InputMapping::InputMapping(KeyMapOptions keyMap){
    if(keyMap == WASD){
        command_map = {
            {SDLK_s, std::make_shared<DownCommand>()},
            {SDLK_a, std::make_shared<LeftCommand>()},
            {SDLK_d, std::make_shared<RightCommand>()},
            {SDLK_e, std::make_shared<RotateClockwiseCommand>()},
            {SDLK_q, std::make_shared<RotateCounterClockwiseCommand>()}
        };
    } else if (keyMap == ARROWS){
        command_map = {
            {SDLK_DOWN, std::make_shared<DownCommand>()},
            {SDLK_LEFT, std::make_shared<LeftCommand>()},
            {SDLK_RIGHT, std::make_shared<RightCommand>()},
            {SDLK_UP, std::make_shared<RotateClockwiseCommand>()}
        };
    }
}

void InputMapping::bindKey(SDL_Keycode key, command_ptr command){
    command_map[key] = command;
}

void InputMapping::setNewTarget(Tetrominos& tetro){
    for(auto& [_, command] : command_map){
        command->bindNewPiece(tetro);
    }
}

InputMapping::command_ptr InputMapping::getCommand(SDL_Keycode key) const {
    auto it = command_map.find(key); // Use find to locate the key
    if (it != command_map.end()) {
        return it->second; // Access the value via the iterator
    }
    return nullptr; // Return nullptr if the key is not found
}