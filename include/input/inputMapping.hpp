#pragma once

#include "pch.h"

#include "commands/commands.hpp"

struct Input{
    SDL_EventType type;
    char key;
};

struct KeyCommands{
    using CommandPair = std::pair<KeyCode, std::shared_ptr<ICommands>>;
    CommandPair RIGHT;
    CommandPair LEFT;
    CommandPair DOWN;
    CommandPair ROTATE_CLOCKWISE;
    CommandPair ROTATE_COUNTERCLOCKWISE;
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
    const KeyCommands keyCommands;
    std::unordered_map<SDL_Keycode, command_ptr> command_map;

public:
    InputMapping(KeyMapOptions keyMap);
    const KeyCommands& getKeyCommands() const { return keyCommands; }
    void bindKey(SDL_Keycode key, command_ptr command);
    void setNewTarget(Tetrominos* tetro);
    command_ptr getCommand(SDL_Keycode) const;
    void Reset();
};