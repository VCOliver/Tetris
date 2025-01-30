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
    static void Info(const std::string& message);
    static void Warning(const std::string& message);
    static void Error(const std::string& message);
    static void Debug(const std::string& message);

private:
    // Private constructor to prevent instantiation
    Log() = default;

};

#ifdef DEBUG_LOGGING
    #define LOG_INFO(message) Log::Info(message)
    #define LOG_WARNING(message) Log::Warning(message)
    #define LOG_ERROR(message) Log::Error(message)
    #define LOG_DEBUG(message) Log::Debug(message)
#endif