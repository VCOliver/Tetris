#pragma once

#include <SDL2/SDL.h>

#include "utils/position.hpp"

#define STD_BLOCK_W 20
#define STD_BLOCK_H 20 
#define STD_LINE_THICKNESS 2

/// @brief Render components Interface
class IRenderComponent{
public:
    virtual ~IRenderComponent() = default;
    virtual void render(SDL_Renderer* renderer) const = 0;        
};

class BorderLine : public IRenderComponent {
    int thickness;
    SDL_Rect lines[2];

public:
    BorderLine(Position start_pos, int thickness=STD_LINE_THICKNESS);

    void render(SDL_Renderer* renderer) const;
};

class Block : public IRenderComponent{
    Position pos;
    int width;
    int height;
    int alpha;
    BorderLine* border;

public:
    Block(Position pos, int w=STD_BLOCK_W, int h=STD_BLOCK_H, int alpha=255);
    ~Block();

    void render(SDL_Renderer* renderer) const override;
};