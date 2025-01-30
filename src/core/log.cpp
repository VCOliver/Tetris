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