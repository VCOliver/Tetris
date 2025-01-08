#include <iostream>

#include "components/renderComponents.hpp"
#include "utils/colors.hpp"
#include "utils/renderUtils.hpp"

BlockBorder::BlockBorder(Position start_position, int thickness)
    : thickness(thickness)
{
    Position start_pos = start_position.getRealPosition();
    light[0] =  {start_pos, 
                {start_pos.x + thickness, start_pos.y+thickness}, 
                {start_pos.x, start_pos.y + STD_BLOCK_H}, 
                {start_pos.x + thickness, start_pos.y + STD_BLOCK_H - thickness}};
    light[1] =  {start_pos, 
                {start_pos.x + STD_BLOCK_W, start_pos.y}, 
                {start_pos.x+thickness, start_pos.y + thickness}, 
                {start_pos.x + STD_BLOCK_H - thickness, start_pos.y + thickness}};
    Position end_pos = {start_pos.x + STD_BLOCK_W, start_pos.y + STD_BLOCK_H};
    shadow[0] = {{end_pos.x-STD_BLOCK_W+thickness, end_pos.y-thickness}, 
                {end_pos.x -thickness, end_pos.y-thickness}, 
                {end_pos.x-STD_BLOCK_W, end_pos.y}, 
                end_pos};
    shadow[1] = {{end_pos.x-thickness, end_pos.y-STD_BLOCK_H+thickness}, 
                {end_pos.x, end_pos.y-STD_BLOCK_H}, 
                {end_pos.x-thickness, end_pos.y-thickness}, 
                end_pos};
}


void BlockBorder::render(SDL_Renderer* renderer) const {
    Color color = Colors::WHITE;
    SDL_SetRenderDrawBlendMode(renderer, BLENDMODE); // Enable blending mode
    SDL_SetRenderDrawColor(renderer, color.red, color.green, color.blue, OPAQUE);

    // Draw upper border lines
    for(int i = 0; i < 2; i++){
        render::renderDrawTrapz(renderer, light[i]);  
    }

    render::renderFillTrapz(renderer, light[0]);

    color = Colors::BLACK;
    SDL_SetRenderDrawColor(renderer, color.red, color.green, color.blue, OPAQUE);

    // Draw lower border lines
    for(int i = 0; i < 2; i++){
        render::renderDrawTrapz(renderer, shadow[i]);  
    }

    // Deactivate blending mode
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
}

Block::Block(Position pos, int w, int h, int alpha)
            : pos(pos), width(w), height(h){
    if(alpha > 255 || alpha < 0){
        std::cerr << "Opacity cannot be lower than 0\% or greater than 100\%" << std::endl;
        exit(1);
    }

    this->alpha = alpha;

    border = new BlockBorder(pos);
}

Block::~Block(){
    delete border;
}

void Block::render(SDL_Renderer* renderer) const {
    Position p = this->pos.getRealPosition();
    int h = this->height;
    int w = this->width;

    SDL_Rect square = { p.x, p.y, w, h }; // x, y, width, height

    // Draw square (borders)
    SDL_RenderDrawRect(renderer, &square);

    // Fill square
    SDL_RenderFillRect(renderer, &square);

    border->render(renderer);

}