#pragma once

#include <SDL2/SDL.h>

#include "tetrion.hpp"
#include "utils/renderUtils.hpp"
#include "systems/renderSystem.hpp"

/**
 * @class Game
 * @brief Manages the game lifecycle including initialization, running, and closing.
 */
class Game {
    int width, height; ///< Width and height of the game window.

    SDL_Window* window; ///< Pointer to the SDL_Window.
    SDL_Renderer* renderer; ///< Pointer to the SDL_Renderer.
    SDL_Event event; ///< SDL_Event for handling events.

    RenderSystem* renderSystem; ///< Pointer to the RenderSystem for managing rendering.

public:
    /**
     * @brief Constructs a Game with the specified width and height.
     * 
     * @param w Width of the game window.
     * @param h Height of the game window.
     */
    Game(int w, int h);

    /**
     * @brief Initializes the game, including SDL and the rendering system.
     */
    void init();

    /**
     * @brief Runs the main game loop.
     */
    void run();

    /**
     * @brief Closes the game, cleaning up resources.
     */
    void close();
};