#include "core/log.hpp"

void Log::Info(const std::string& message){
    std::cout << COLOR_INFO << "[INFO] " << message << COLOR_RESET << std::endl;
}

void Log::Warning(const std::string& message){
    std::cout << COLOR_WARNING << "[WARNING] " << message << COLOR_RESET << std::endl;
}

void Log::Error(const std::string& message){
    std::cout << COLOR_ERROR << "[ERROR] " << message << COLOR_RESET << std::endl;
}

void Log::Debug(const std::string& message){
    std::cout << COLOR_DEBUG << "[DEBUG] " << message << COLOR_RESET << std::endl;
}