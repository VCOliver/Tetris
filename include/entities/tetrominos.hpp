#pragma once

#include <unordered_map>

#include "utils/shapes.hpp"
#include "components/renderComponents.hpp"

#define TETROMINOS_MATRIX_H 4
#define TETROMINOS_MATRIX_W 4

class Tetrominos {
using shapes_map = std::unordered_map<char, shapes::Matrix>;

private:
    shapes::Matrix matrix;
    shapes_map shapes;
    Position start_pos;

public:
    Tetrominos(Position start_pos);

    void render(SDL_Renderer* renderer) const;
};