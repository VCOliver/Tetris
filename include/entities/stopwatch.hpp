#pragma once

#include <iostream>
#include <functional>
#include <thread>
#include <atomic>
#include <tuple>
#include <string>
#include <mutex>
#include <SDL2/SDL.h>

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

class StopwatchBlock : public Renderable {
private:
    static constexpr int h = 5;
    static constexpr int w = 6;
    int time;
    std::mutex& mtx;
    Position start_pos;
    FontSystem* fontSystem;
    math::Matrix<std::tuple<Position, bool>, h, w> matrix;

public: 
    StopwatchBlock(Position start_pos, FontSystem* fontSystem, std::mutex& time_mutex);

    void setTime(int time);
    int getTime() const ;

    void render(SDL_Renderer* renderer) const;
};