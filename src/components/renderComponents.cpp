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
    SDL_SetRenderDrawBlendMode(renderer, BLENDMODE); // Enable blending mode
    render::setRenderDrawColor(renderer, Colors::WHITE, 80);

    // Draw upper border lines
    for(int i = 0; i < 2; i++){
        render::renderFillTrapz(renderer, light[i]);  
    }
    
    render::setRenderDrawColor(renderer, Colors::BLACK, 127);

    // Draw lower border lines
    for(int i = 0; i < 2; i++){
        render::renderFillTrapz(renderer, shadow[i]);  
    }

    // Deactivate blending mode
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_NONE);
}

Block::Block(Position pos, Color color, int w, int h, rgba_t alpha)
            : pos(pos), color(color), width(w), height(h), alpha(alpha){

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

    render::setRenderDrawColor(renderer, color);

    // Fill square
    SDL_RenderFillRect(renderer, &square);

    border->render(renderer);

}