#pragma once

#include "pch.h"

#include "components/renderComponents.hpp"
#include "utils/renderUtils.hpp"
#include "utils/mathUtils.hpp"

#define TETRION_H 24
#define TETRION_W 12

class Tetrion : public Renderable{
using Matrix = math::Matrix<std::tuple<Position, bool>, TETRION_H, TETRION_W>;

private:
    Matrix matrix;

    Position start_pos;

public:
    Tetrion(Position start_pos);

    void render(SDL_Renderer* renderer) const ;
};