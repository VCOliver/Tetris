#pragma once

#include <iostream>
#include <functional>
#include <thread>
#include <atomic>

#include "utils/renderUtils.hpp"

class Stopwatch {
private:
    std::thread stopwatch_thread;
    std::atomic<bool> running;
    std::atomic<int> elapsed_time; // in milliseconds

public:
    Stopwatch();

    void start(std::function<void(int)> callback, int interval_ms = 1000);
    void stop();
    void reset();
    ~Stopwatch();
};