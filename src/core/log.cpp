#include "core/log.hpp"

void Log::LogMessage(Level level, const std::string& msg) {
    switch (level) {
        case Level::INFO:
            std::cout << COLOR_INFO << "[INFO] " << msg << COLOR_RESET << std::endl;
            break;
        case Level::WARNING:
            std::cout << COLOR_WARNING << "[WARNING] " << msg << COLOR_RESET << std::endl;
            break;
        case Level::ERROR:
            std::cerr << COLOR_ERROR << "[ERROR] " << msg << COLOR_RESET << std::endl;
            break;
        case Level::DEBUG:
            std::cout << COLOR_DEBUG << "[DEBUG] " << msg << COLOR_RESET << std::endl;
            break;
    }
}

namespace LogUtils{
    void UpdateFPS(Uint32 currentTime) {
        static Uint32 previousTime = 0;
        static int frameCount = 0;
        static float accumulatedTime = 0;
        auto deltaTime = (currentTime - previousTime) / 1000.0f; // In seconds
        previousTime = currentTime;
        accumulatedTime += deltaTime;
        frameCount++;

        int fps = 0;
        if (accumulatedTime >= 1.0f) {
            fps = frameCount;
            frameCount = 0;
            accumulatedTime -= 1.0f;

            // Print FPS
            LOG_DEBUG("FPS: ", fps);
        }
    }
}