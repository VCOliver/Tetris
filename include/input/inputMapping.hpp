#pragma once

#include "pch.h"

#include "commands/commands.hpp"

struct Input{
    SDL_EventType type;
    char key;
};

class InputMapping {
public:
    using Command = ICommands*;
    using command_ptr = std::shared_ptr<Command>;
private:
    std::unordered_map<SDL_Keycode, command_ptr> command_map;

public:
    InputMapping();

    void bindKey(SDL_Keycode key, command_ptr command);
    command_ptr getCommand(SDL_Keycode) const;
};