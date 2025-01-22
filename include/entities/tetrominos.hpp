#pragma once

#include "pch.h"

#include "utils/shapes.hpp"
#include "utils/colors.hpp"
#include "utils/mathUtils.hpp"
#include "utils/renderUtils.hpp"
#include "components/renderComponents.hpp"

class Tetrominos : public Renderable {
public:
    enum AllowedMovementDirections {
        RIGHT,
        LEFT,
        DOWN
    };

private:
    using Matrix = math::Matrix<std::tuple<Position, bool>, SHAPES_MATRIX_H, SHAPES_MATRIX_W>;
    using shapes_map = std::unordered_map<char, shapes::Matrix>;
    using Dir = AllowedMovementDirections;
    Matrix matrix;
    Position start_pos;
    Color color;
    void moveDown();

public:

    Tetrominos(Position start_pos, Color color);
    Tetrominos(Position start_pos, Color color, shapes::Matrix shape);

    shapes::Matrix getRandomShape() const;

    void move(Dir dir);

    void render(SDL_Renderer* renderer) const;
};