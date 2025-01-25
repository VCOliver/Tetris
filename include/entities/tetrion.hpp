#pragma once

#include "pch.h"
#include "core/base.hpp"

#include "components/renderComponents.hpp"
#include "systems/renderSystem.hpp"
#include "utils/mathUtils.hpp"

class Tetrion : public Renderable{
using Matrix = math::Matrix<std::tuple<Position, bool>, TETRION_H, TETRION_W>;

private:
    Matrix matrix;

    Position start_pos;

public:
    Tetrion(Position start_pos);

    void render() const ;
};