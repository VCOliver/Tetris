#include "entities/playfield.hpp"

Playfield::Playfield(Position pos) : start_pos(pos){
    tetrion = new Tetrion(start_pos);
    int x = std::rand() % (TETRION_W-SHAPES_MATRIX_W-1);
    x++;
    Position tetromino_pos = {start_pos.x+x, start_pos.y-1};
    tetromino = new Tetrominos(tetromino_pos, Colors::RED);
}

Playfield::~Playfield(){
    delete tetrion;
    delete tetromino;
}

void Playfield::render(SDL_Renderer* renderer) const {
    tetromino->render(renderer); // Renders Tetromino

    // Cover Tetromino part above Tetrion
    SDL_Point p = start_pos.getRealPosition();
    int w = (TETRION_W+1)*20;
    int h = p.y;
    p.y = 0;
    SDL_Rect rect = {p.x, p.y, w, h};
    render::setRenderDrawColor(renderer, Colors::BLACK);
    SDL_RenderFillRect(renderer, &rect);

    // // Renders Tetrion
    tetrion->render(renderer);
}