#pragma once

class ICommands {
public:
    virtual ~ICommands() = default;
    virtual void execute() = 0;
};

using Command = ICommands;