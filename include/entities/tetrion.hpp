#pragma once

#include <array>
#include <tuple>

#include "components/renderComponents.hpp"
#include "utils/renderUtils.hpp"

#define TETRION_H 24
#define TETRION_W 12

class Tetrion : public IRenderComponent{
using Matrix = std::array<std::array<std::tuple<Position, bool>, TETRION_W>, TETRION_H>;

private:
    Matrix matrix;

    Position start_pos;

public:
    Tetrion(Position start_pos);

    void render(SDL_Renderer* renderer) const ;
};