#include "entities/playfield.hpp"

Playfield::Playfield(Position pos) : start_pos(pos){
    tetrion = new Tetrion(start_pos);
}

Playfield::~Playfield(){
    delete tetrion;
}

void Playfield::render(SDL_Renderer* renderer) const {
    SDL_Point p = start_pos.getRealPosition();
    int w = (TETRION_W+1)*20;
    int h = p.y;
    p.y = 0;
    SDL_Rect rect = {p.x, p.y, w, h};
    render::setRenderDrawColor(renderer, Colors::BLACK);
    SDL_RenderFillRect(renderer, &rect);

    tetrion->render(renderer);
}