#pragma once

#include <SDL2/SDL.h>

#include "utils/position.hpp"
#include "component.hpp"
#include "utils/colors.hpp"

/// @brief Render components Interface
/**
 * @class IRenderComponent
 * @brief Interface for renderable components in the Tetris game.
 *
 * This interface defines the contract for any renderable component
 * within the Tetris game. Classes that inherit from IRenderComponent
 * must implement the render method to handle their specific rendering logic.
 */
class IRenderComponent{
public:
    virtual ~IRenderComponent() = default;
    virtual void render(SDL_Renderer* renderer) const = 0;        
};

/**
 * @struct Trapezium
 * @brief Represents a trapezium shape with four positions.
 */
struct Trapezium {
    SDL_Point top_left; ///< Top-left position of the trapezium.
    SDL_Point top_right; ///< Top-right position of the trapezium.
    SDL_Point bottom_left; ///< Bottom-left position of the trapezium.
    SDL_Point bottom_right; ///< Bottom-right position of the trapezium.

    Trapezium() = default;
};

/**
 * @class BlockBorder
 * @brief Represents the border of a block with light and shadow trapeziums.
 */
class BlockBorder : public IRenderComponent {
private:
    int thickness; ///< Thickness of the border.
    Trapezium light[2]; ///< Light trapeziums for the border.
    Trapezium shadow[2]; ///< Shadow trapeziums for the border.

public:
    /**
     * @brief Constructs a BlockBorder with the given start position and thickness.
     * 
     * @param start_position The starting position of the border.
     * @param thickness The thickness of the border. Default is STD_LINE_THICKNESS.
     */
    BlockBorder(Position start_position, int thickness=STD_LINE_THICKNESS);

    /**
     * @brief Renders the block border using the given SDL_Renderer.
     * 
     * @param renderer Pointer to the SDL_Renderer.
     */
    void render(SDL_Renderer* renderer) const override;
};

/**
 * @class Block
 * @brief Represents a block with a position, dimensions, alpha value, and an optional border.
 */
class Block : public IRenderComponent {
    Position pos; ///< Position of the block.
    Color color;
    int width; ///< Width of the block.
    int height; ///< Height of the block.
    rgba_t alpha; ///< Alpha transparency value of the block.
    BlockBorder* border; ///< Pointer to the block's border.

public:
    /**
     * @brief Constructs a Block with the given position, width, height, and alpha value.
     * 
     * @param pos The position of the block.
     * @param w The width of the block. Default is STD_BLOCK_W.
     * @param h The height of the block. Default is STD_BLOCK_H.
     * @param alpha The alpha transparency value of the block. Default is 255.
     */
    Block(Position pos, Color color, int w=STD_BLOCK_W, int h=STD_BLOCK_H, rgba_t alpha=255);

    /**
     * @brief Destructor for the Block.
     */
    ~Block();

    /**
     * @brief Renders the block using the given SDL_Renderer.
     * 
     * @param renderer Pointer to the SDL_Renderer.
     */
    void render(SDL_Renderer* renderer) const override;
};