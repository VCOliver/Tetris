#pragma once

#include "pch.h"
#include "core/base.hpp"

#include "components/renderComponents.hpp"
#include "systems/renderSystem.hpp"
#include "utils/mathUtils.hpp"

class Tetrion : public Renderable{
using drawMatrix = math::Matrix<std::tuple<Position, bool>, TETRION_H, TETRION_W>;
using OccupiedMatrix = math::Matrix<bool, TETRION_H, TETRION_W>;

private:
    drawMatrix matrix;
    OccupiedMatrix occupied;

    Position start_pos;

    void setOccupiedPositions();

public:
    Tetrion(Position start_pos);

    Position getStartPosition() const { return start_pos; }
    Position getLastPosition() const { return start_pos + Position({TETRION_W-1, TETRION_H-1}); }

    void onUpdate();

    bool isPositionFree(Position pos) const;

    void render() const ;
};