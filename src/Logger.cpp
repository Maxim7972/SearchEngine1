#include "Logger.h"
#include <iostream>
#include <ctime>

Logger::Logger() {
    logFile.open("log.txt", std::ios::app);
    if (!logFile.is_open()) {
        throw std::runtime_error("Unable to open log file.");
    }
}

Logger::~Logger() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

Logger& Logger::GetInstance() {
    static Logger instance;
    return instance;
}

void Logger::Log(const std::string& message) {
    std::lock_guard<std::mutex> lock(logMutex);
    std::time_t now = std::time(nullptr);
    logFile << std::ctime(&now) << ": " << message << std::endl;
}
