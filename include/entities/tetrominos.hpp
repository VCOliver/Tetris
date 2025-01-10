#pragma once

#include <array>
#include <tuple>
#include <unordered_map>

#include "utils/shapes.hpp"
#include "components/renderComponents.hpp"

class Tetrominos {
using Matrix = std::array<std::array<std::tuple<Position, bool>, SHAPES_MATRIX_W>, SHAPES_MATRIX_H>;
using shapes_map = std::unordered_map<char, Matrix>;

private:
    Matrix matrix;
    shapes_map shapes;
    Position start_pos;

public:
    Tetrominos(Position start_pos);

    void render(SDL_Renderer* renderer) const;
};