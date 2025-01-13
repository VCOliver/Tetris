#pragma once

#include <array>
#include <tuple>
#include <unordered_map>

#include "utils/shapes.hpp"
#include "utils/colors.hpp"
#include "utils/mathUtils.hpp"
#include "utils/renderUtils.hpp"
#include "components/renderComponents.hpp"

class Tetrominos : public Renderable {
using Matrix = math::Matrix<std::tuple<Position, bool>, SHAPES_MATRIX_H, SHAPES_MATRIX_W>;
using shapes_map = std::unordered_map<char, shapes::Matrix>;

private:
    Matrix matrix;
    Position start_pos;
    Color color;

public:
    Tetrominos(Position start_pos, Color color);

    shapes::Matrix getRandomShape() const;

    void render(SDL_Renderer* renderer) const;
};