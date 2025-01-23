#pragma once

#include <queue>

#include "pch.h"

#include "window.hpp"
#include "entities/tetrominos.hpp"
#include "entities/playfield.hpp"
#include "entities/stopwatch.hpp"
#include "entities/score.hpp"
#include "utils/renderUtils.hpp"
#include "systems/renderSystem.hpp"
#include "systems/fontSystem.hpp"
#include "events/event.hpp"
#include "events/keyEvent.hpp"
#include "events/windowEvent.hpp"
#include "events/eventDispatcher.hpp"
#include "input/inputManager.hpp"

constexpr int FRAME_RATE = 24;
constexpr int FRAME_DELAY = 1000 / FRAME_RATE; // Time per frame in milliseconds

/**
 * @class Game
 * @brief Manages the game lifecycle including initialization, running, and closing.
 */
class Game {
    int width, height; ///< Width and height of the game window.

    std::unique_ptr<Window> window;
    SDL_Renderer* renderer; ///< Pointer to the SDL_Renderer.

    InputManager* inputManager;
    RenderSystem* renderSystem; ///< Pointer to the RenderSystem for managing rendering.
    FontSystem* fontSystem;
    Stopwatch* stopwatch;

    bool running = true;
    std::queue<std::unique_ptr<Event>> eventQueue;

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

private:
    void processEvents();
    void update();
    bool onWindowClose(WindowCloseEvent& e);
};