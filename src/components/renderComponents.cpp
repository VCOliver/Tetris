#include <iostream>

#include "components/renderComponents.hpp"
#include "utils/colors.hpp"
#include "systems/renderSystem.hpp"

BlockBorder::BlockBorder(Position start_position, int thickness)
    : thickness(thickness)
{
    SDL_Point start_pos = start_position.getRealPosition();
    light[0] =  {start_pos, 
                {start_pos.x + thickness, start_pos.y+thickness}, 
                {start_pos.x, start_pos.y + STD_BLOCK_H}, 
                {start_pos.x + thickness, start_pos.y + STD_BLOCK_H - thickness}};
    light[1] =  {start_pos, 
                {start_pos.x + STD_BLOCK_W, start_pos.y}, 
                {start_pos.x+thickness, start_pos.y + thickness}, 
                {start_pos.x + STD_BLOCK_H - thickness, start_pos.y + thickness}};
    SDL_Point end_pos = {start_pos.x + STD_BLOCK_W, start_pos.y + STD_BLOCK_H};
    shadow[0] = {{end_pos.x-STD_BLOCK_W+thickness, end_pos.y-thickness}, 
                {end_pos.x -thickness, end_pos.y-thickness}, 
                {end_pos.x-STD_BLOCK_W, end_pos.y}, 
                end_pos};
    shadow[1] = {{end_pos.x-thickness, end_pos.y-STD_BLOCK_H+thickness}, 
                {end_pos.x, end_pos.y-STD_BLOCK_H}, 
                {end_pos.x-thickness, end_pos.y-thickness}, 
                end_pos};
}


void BlockBorder::render() const {
    Renderer::setDrawBlendMode(BlendMode::BLEND); // Enable blending mode
    Renderer::setRenderDrawColor(Colors::WHITE, 80);

    // Draw upper border lines
    for(int i = 0; i < 2; i++){
        Renderer::FillTrapz(light[i]);
    }
    
    Renderer::setRenderDrawColor(Colors::BLACK, 127);

    // Draw lower border lines
    for(int i = 0; i < 2; i++){
        Renderer::FillTrapz(shadow[i]);
    }

    // Deactivate blending mode
    Renderer::setDrawBlendMode(BlendMode::NONE);
}

Block::Block(Position pos, Color color, int w, int h, rgba_t alpha)
            : pos(pos), color(color), width(w), height(h), alpha(alpha){

    border = new BlockBorder(pos);
}

Block::~Block(){
    delete border;
}

void Block::render() const {
    Renderer::setRenderDrawColor(color);

    // Fill square
    Renderer::FillRect(pos, width, height);

    border->render();

}