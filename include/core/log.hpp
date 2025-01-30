#pragma once

#include "pch.h"

// ANSI color codes for terminal output
#define COLOR_RESET   "\033[0m"
#define COLOR_INFO    "\033[37m" // White
#define COLOR_WARNING "\033[33m" // Yellow
#define COLOR_ERROR   "\033[31m" // Red
#define COLOR_DEBUG   "\033[36m" // Cyan

class Log {
public:
    // Enum for log levels
    enum class Level {
        INFO,    // Informational messages
        WARNING, // Warning messages
        ERROR,   // Error messages
        DEBUG    // Debug messages (for debugging purposes)
    };

    // Static method to log messages with a specific level
    template <typename... Args>
    static void Info(Args&&... args) {
        std::ostringstream oss;
        (oss << ... << args);
        LogMessage(Level::INFO, oss.str());
    }

    template <typename... Args>
    static void Warning(Args&&... args) {
        std::ostringstream oss;
        (oss << ... << args);
        LogMessage(Level::WARNING, oss.str());
    }

    template <typename... Args>
    static void Error(Args&&... args) {
        std::ostringstream oss;
        (oss << ... << args);
        LogMessage(Level::ERROR, oss.str());
    }

    template <typename... Args>
    static void Debug(Args&&... args) {
        std::ostringstream oss;
        (oss << ... << args);
        LogMessage(Level::DEBUG, oss.str());
    }

private:
    // Private constructor to prevent instantiation
    Log() = default;

    static void LogMessage(Level level, const std::string& msg);

};

#ifdef DEBUG_LOGGING
    #define LOG_INFO(...) Log::Info(__VA_ARGS__)
    #define LOG_WARNING(...) Log::Warning(__VA_ARGS__)
    #define LOG_ERROR(...) Log::Error(__VA_ARGS__)
    #define LOG_DEBUG(...) Log::Debug(__VA_ARGS__)
#else
    #define LOG_INFO(...)
    #define LOG_WARNING(...)
    #define LOG_ERROR(...)
    #define LOG_DEBUG(...)
#endif

namespace LogUtils {
    void UpdateFPS(Uint32 currentTime);
}