#pragma once

#include "pch.h"

#include "commands/commands.hpp"

struct Input{
    SDL_EventType type;
    char key;
};

enum KeyMapOptions{
    WASD,
    ARROWS
};

class InputMapping {
public:
    using Command = ICommands;
    using command_ptr = std::shared_ptr<Command>;
private:
    std::unordered_map<SDL_Keycode, command_ptr> command_map;

public:
    InputMapping(KeyMapOptions keyMap);

    void bindKey(SDL_Keycode key, command_ptr command);
    void setNewTarget(Tetrominos* tetro);
    command_ptr getCommand(SDL_Keycode) const;
};