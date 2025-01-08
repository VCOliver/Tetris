#include "core/tetrion.hpp"

Tetrion::Tetrion(Position start_pos)
    : start_pos(START_POSITION){
    Position p;
    bool visible = false;;
    for(int y = 0; y<TETRION_H; y++){
        for(int x = 0; x<TETRION_W; x++){
            p = {start_pos.x + x, start_pos.y + y};
            if(x == 0 || y == 0 || x == TETRION_W-1 || y == TETRION_H){
                visible=true;
            }
            matrix[x][y] = std::make_tuple(p, visible);
            visible=false;
        }
    }
}

