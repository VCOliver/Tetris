#pragma once

#include <unordered_map>
#include <memory>
#include <SDL2/SDL.h>

#include "commands/commands.hpp"

struct Input{
    SDL_EventType type;
    char key;
};

class InputMapping {
public:
    using command_ptr = std::shared_ptr<Command>;
private:
    std::unordered_map<SDL_KeyCode, command_ptr> command_map;

public:
    InputMapping();

    void bindKey(SDL_KeyCode key, command_ptr command);
    command_ptr getCommand(SDL_KeyCode) const;
};