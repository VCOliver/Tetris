#include <iostream>

#include "components/renderComponents.hpp"
#include "utils/colors.hpp"

BorderLine::BorderLine(Position start_pos, int thickness)
    : thickness(thickness){
    Position p = start_pos.getRealPosition();
    this->lines[0] = {p.x, p.y, thickness, STD_BLOCK_H};
    this->lines[1] = {p.x+thickness, p.y, STD_BLOCK_W-thickness, thickness};
    this->lines[2] = {p.x + STD_BLOCK_W - thickness, p.y+thickness, thickness, STD_BLOCK_H-thickness};
    this->lines[3] = {p.x+thickness, p.y + STD_BLOCK_H - thickness, STD_BLOCK_W-2*thickness, thickness};
}

void BorderLine::render(SDL_Renderer* renderer) const {
    Color color = Colors::WHITE;
    SDL_SetRenderDrawBlendMode(renderer, BLENDMODE); // Enable blending mode
    SDL_SetRenderDrawColor(renderer, color.red, color.green, color.blue, 127);

    // Draw upper border lines
    for(int i = 0; i < 2; i++){
        //SDL_RenderDrawRect(renderer, &lines[i]);
        SDL_RenderFillRect(renderer, &lines[i]);  
    }

    color = Colors::BLACK;
    SDL_SetRenderDrawColor(renderer, color.red, color.green, color.blue, 127);

    // Draw lower border lines
    for(int i = 2; i < 4; i++){
        //SDL_RenderDrawRect(renderer, &lines[i]);
        SDL_RenderFillRect(renderer, &lines[i]);  
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

    border = new BorderLine(pos);
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