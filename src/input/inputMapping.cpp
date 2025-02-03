#include "input/inputMapping.hpp"

InputMapping::InputMapping(KeyMapOptions keyMap)
    : keyCommands([keyMap]() -> KeyCommands {
          if(keyMap == WASD)
              return KeyCommands {std::make_pair(SDLK_d, std::make_shared<RightCommand>()), 
                                  std::make_pair(SDLK_a, std::make_shared<LeftCommand>()),
                                  std::make_pair(SDLK_s, std::make_shared<DownCommand>()),
                                  std::make_pair(SDLK_e, std::make_shared<RotateClockwiseCommand>()),
                                  std::make_pair(SDLK_q, std::make_shared<RotateCounterClockwiseCommand>())};
          else if(keyMap == ARROWS)
              return KeyCommands {std::make_pair(SDLK_RIGHT, std::make_shared<RightCommand>()),
                                  std::make_pair(SDLK_LEFT, std::make_shared<LeftCommand>()),
                                  std::make_pair(SDLK_DOWN, std::make_shared<DownCommand>()),
                                  std::make_pair(SDLK_UP, std::make_shared<RotateClockwiseCommand>())};
          else
              return KeyCommands{};  // Default case if needed.
      }())
{
    // Initialize command_map based on keyMap.
    Reset();
}


void InputMapping::Reset(){
    command_map.clear();
    command_map = {
        {keyCommands.RIGHT.first, keyCommands.RIGHT.second},
        {keyCommands.LEFT.first, keyCommands.LEFT.second},
        {keyCommands.DOWN.first, keyCommands.DOWN.second},
        {keyCommands.ROTATE_CLOCKWISE.first, keyCommands.ROTATE_CLOCKWISE.second},
        {keyCommands.ROTATE_COUNTERCLOCKWISE.first, keyCommands.ROTATE_COUNTERCLOCKWISE.second}
    };
}

void InputMapping::bindKey(SDL_Keycode key, command_ptr command){
    command_map[key] = command;
}

void InputMapping::setNewTarget(Tetrominos* tetro){
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