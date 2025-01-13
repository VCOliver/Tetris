

#include "entities/tetrion.hpp"

Tetrion::Tetrion(Position start_pos)
    : start_pos(START_POSITION){
    Position p;
    bool visible = false;
    for(int y = 0; y<TETRION_H; y++){
        for(int x = 0; x<TETRION_W; x++){
            p = {start_pos.x + x, start_pos.y + y};
            if(x == 0 || y == 0 || x == TETRION_W-1 || y == TETRION_H-1){
                visible=true;
            }
            matrix(y, x) = std::make_tuple(p, visible);
            visible=false;
        }
    }
}

void Tetrion::render(SDL_Renderer* renderer) const {
    for(auto& row : matrix){
        for(auto& [pos, visible] : row){
            if(visible){
                Block block = Block(pos, Colors::GRAY);
                block.render(renderer);
            }
        }
    }
}