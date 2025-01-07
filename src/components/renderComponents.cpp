#include <iostream>

#include "components/renderComponents.hpp"
#include "utils/colors.hpp"

BorderLine::BorderLine(Position start_pos, int thickness)
    : thickness(thickness){
    Position p = start_pos.getRealPosition();
    this->lines[0] = {p.x, p.y, thickness, STD_BLOCK_H};
    this->lines[1] = {p.x, p.y, STD_BLOCK_W, thickness};
}

void BorderLine::render(SDL_Renderer* renderer) const {
    Color color = Colors::WHITE;
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND); // Enable blending mode
    SDL_SetRenderDrawColor(renderer, color.red, color.green, color.blue, 127);

    // Draw upper border lines
    SDL_RenderDrawRect(renderer, &lines[0]);
    SDL_RenderFillRect(renderer, &lines[0]);
    SDL_RenderDrawRect(renderer, &lines[1]);
    SDL_RenderFillRect(renderer, &lines[1]);

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