#pragma once

#include "utils/position.hpp"

struct Block {
    Position pos;
    int width;
    int height;
    int alpha;

    Block(Position pos, int w, int h, int alpha=255);
};