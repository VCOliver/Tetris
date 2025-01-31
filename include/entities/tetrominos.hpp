#pragma once

#include "pch.h"

#include "utils/shapes.hpp"
#include "utils/colors.hpp"
#include "utils/mathUtils.hpp"
#include "systems/renderSystem.hpp"
#include "components/renderComponents.hpp"

/**
 * @class Tetrominos
 * @brief Represents a Tetromino, a geometric shape composed of four squares, used in games like Tetris.
 * @extends IRenderComponent
 * 
 * This class manages the position, movement, and rendering of Tetromino shapes.
 */
class Tetrominos : public Renderable {
public:
    /**
     * @enum AllowedMovements
     * @brief Defines the allowed movement directions for a Tetromino.
     */
    enum AllowedMovements {
        RIGHT, /**< Move the Tetromino to the right. */
        LEFT,  /**< Move the Tetromino to the left. */
        DOWN,   /**< Move the Tetromino downward. */
        ROTATE_CLOCKWISE, /** Rotatee the Tetromino clockwise */
        ROTATE_COUNTERCLOCKWISE /** Rotate the Tetromino counterclockwise */
    };

private:
    /**
     * @typedef Matrix
     * @brief A matrix representing the Tetromino's shape and position.
     * 
     * Each element in the matrix is a tuple containing:
     * - A `Position` object representing the position of the square.
     * - A `bool` indicating whether the square is occupied.
     */
    using Matrix = math::Matrix<std::tuple<Position, bool>, SHAPES_MATRIX_H, SHAPES_MATRIX_W>;

    /**
     * @typedef shapes_map
     * @brief A map that associates a character key with a Tetromino shape.
     */
    using shapes_map = std::unordered_map<char, shapes::Matrix>;

    /**
     * @typedef Dir
     * @brief A shorthand for the AllowedMovements enum.
     */
    using Dir = AllowedMovements;

    Matrix matrix;          /**< The matrix representing the Tetromino's current state. */
    shapes::Matrix shape;           /**< The shape of the Tetromino. */
    Position start_pos;     /**< The starting position of the Tetromino. */
    Color color;            /**< The color of the Tetromino. */

    /**
     * @brief Moves the Tetromino downward.
     */
    void moveDown();

    /**
     * @brief Moves the Tetromino to the left.
     */
    void moveLeft();

    /**
     * @brief Moves the Tetromino to the right.
     */
    void moveRight();

    void rotateClockwise();

    void rotateCounterClockwise();

public:
    /**
     * @brief Constructor for Tetrominos.
     * @param start_pos The starting position of the Tetromino.
     * @param color The color of the Tetromino.
     */
    Tetrominos(Position start_pos, Color color);

    /**
     * @brief Constructor for Tetrominos with a predefined shape.
     * @param start_pos The starting position of the Tetromino.
     * @param color The color of the Tetromino.
     * @param shape The shape of the Tetromino.
     */
    Tetrominos(Position start_pos, Color color, shapes::Matrix shape);

    /**
     * @brief Generates a random Tetromino shape.
     * @return A shapes::Matrix representing the random shape.
     */
    shapes::Matrix getRandomShape() const;

    /**
     * @brief Moves the Tetromino in the specified direction.
     * @param dir The direction to move the Tetromino (RIGHT, LEFT, or DOWN).
     */
    void move(Dir dir);

    void rotate(Dir rollDir);

    shapes::OccupiedPositionsArray getOccupiedPositions() const;

    /**
     * @brief Renders the Tetromino on the screen.
     * @note This method overrides the `render` method from the `Renderable` base class.
     */
    void render() const override;
};