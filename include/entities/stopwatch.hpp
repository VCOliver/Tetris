#pragma once

#include "pch.h"

#include "utils/renderUtils.hpp"
#include "utils/mathUtils.hpp"
#include "systems/fontSystem.hpp"

/**
 * @class Stopwatch
 * @brief A utility class for tracking elapsed time with periodic updates.
 *
 * The `Stopwatch` class provides functionality to start, stop, and reset a timer.
 * It runs in a separate thread to ensure non-blocking operation and supports 
 * user-defined callbacks for periodic updates.
 */
class Stopwatch {
private:
    std::thread stopwatch_thread; ///< Thread used to run the stopwatch.
    std::atomic<bool> running; ///< Atomic flag indicating whether the stopwatch is running.
    std::atomic<int> elapsed_time; ///< Elapsed time in milliseconds.

public:
    /**
     * @brief Default constructor for the `Stopwatch` class.
     * Initializes the stopwatch with no elapsed time and not running.
     */
    Stopwatch();

    /**
     * @brief Starts the stopwatch.
     *
     * Launches a separate thread that updates the elapsed time at regular intervals.
     * The user can specify a callback function that will be called with the elapsed
     * time (in seconds) on each interval.
     *
     * @param callback A function that takes an `int` parameter (elapsed time in seconds) 
     *                 and performs an action (e.g., updating a display).
     * @param interval_ms The interval, in milliseconds, at which the callback is called. 
     *                    Default is 1000 ms (1 second).
     */
    void start(std::function<void(int)> callback, int interval_ms = 1000);

    /**
     * @brief Stops the stopwatch.
     *
     * Halts the thread running the stopwatch and prevents further updates.
     * The elapsed time is preserved until `reset()` is called.
     */
    void stop();

    /**
     * @brief Resets the stopwatch.
     *
     * Sets the elapsed time to zero. If the stopwatch is running, it continues from zero.
     */
    void reset();

    /**
     * @brief Destructor for the `Stopwatch` class.
     *
     * Ensures the thread is properly joined and resources are cleaned up.
     */
    ~Stopwatch();
};

/**
 * @class StopwatchBlock
 * @brief A class representing a stopwatch block that can be rendered on the screen.
 * 
 * This class provides functionality to manage a stopwatch's time, position, and rendering details.
 */
class StopwatchBlock : public Renderable {
private:
    /**
     * @brief Height of the stopwatch block.
     */
    static constexpr int h = 5;

    /**
     * @brief Width of the stopwatch block.
     */
    static constexpr int w = 8;

    /**
     * @brief Current time of the stopwatch in atomic storage for thread safety.
     */
    std::atomic<int> time;

    /**
     * @brief A mutable cache for the current time, used during rendering operations.
     */
    mutable int current_time = 0;

    /**
     * @brief The starting position of the stopwatch block on the screen.
     */
    Position start_pos;

    /**
     * @brief Pointer to the font system used for rendering text.
     */
    FontSystem* fontSystem;

    /**
     * @brief A matrix containing tuples of positions and booleans to define the layout of the stopwatch block.
     */
    math::Matrix<std::tuple<Position, bool>, h, w> matrix;

public:
    /**
     * @brief Constructs a StopwatchBlock object.
     * 
     * @param start_pos The starting position of the stopwatch block.
     * @param fontSystem A pointer to the FontSystem used for rendering text.
     */
    StopwatchBlock(Position start_pos, FontSystem* fontSystem);

    /**
     * @brief Sets the current time of the stopwatch.
     * 
     * @param time The time to set (in arbitrary units).
     */
    void setTime(int time);

    /**
     * @brief Retrieves the current time of the stopwatch.
     * 
     * @return The current time of the stopwatch (in arbitrary units).
     */
    int getTime() const;

    /**
     * @brief Renders the stopwatch block on the screen.
     * 
     * @param renderer A pointer to the SDL_Renderer used for rendering graphics.
     */
    void render(SDL_Renderer* renderer) const;
};
