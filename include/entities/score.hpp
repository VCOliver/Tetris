#pragma once

#include "pch.h"

#include "systems/renderSystem.hpp"
#include "utils/mathUtils.hpp"
#include "systems/fontSystem.hpp"

class ScoreBlock : public Renderable {
private:
    /**
     * @brief Height of the Score block.
     */
    static constexpr int h = 5;

    /**
     * @brief Width of the Score block.
     */
    static constexpr int w = 8;

    /**
     * @brief Pointer to the font system used for rendering text.
     */
    FontSystem* fontSystem;

    int score;

    Position start_pos;
    math::Matrix<std::tuple<Position, bool>, h, w> matrix;

public:
    ScoreBlock(Position pos, FontSystem* fontSystem);

    void increment_score(int points);

    void render() const ;

};