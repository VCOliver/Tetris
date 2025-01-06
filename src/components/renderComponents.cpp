#include <iostream>

#include "components/renderComponents.hpp"

Block::Block(Position pos, int w, int h, int alpha)
            : pos(pos), width(w), height(h){
    if(alpha > 255 || alpha < 0){
        std::cerr << "Opacity cannot be lower than 0\% or greater than 100\%" << std::endl;
        exit(1);
    }

    this->alpha = alpha;
}