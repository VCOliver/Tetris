#pragma once

#include <SDL2/SDL.h>

#include "utils/position.hpp"
#include "component.hpp"

/// @brief Render components Interface
class IRenderComponent{
public:
    virtual ~IRenderComponent() = default;
    virtual void render(SDL_Renderer* renderer) const = 0;        
};


struct Trapezium {
    Position top_left;
    Position top_right;
    Position bottom_left;
    Position bottom_right;

    Trapezium() = default;
};

class BlockBorder : public IRenderComponent {
private:
    int thickness;
    Trapezium light[2];
    Trapezium shadow[2];

public:
    BlockBorder(Position start_position, int thickness=STD_LINE_THICKNESS);

    void render(SDL_Renderer* renderer) const;
};

class Block : public IRenderComponent{
    Position pos;
    int width;
    int height;
    int alpha;
    BlockBorder* border;

public:
    Block(Position pos, int w=STD_BLOCK_W, int h=STD_BLOCK_H, int alpha=255);
    ~Block();

    void render(SDL_Renderer* renderer) const override;
};