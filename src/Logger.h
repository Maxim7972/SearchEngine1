#pragma once
#include <string>
#include <fstream>
#include <mutex>

class Logger {
public:
    static Logger& GetInstance();
    void Log(const std::string& message);

private:
    Logger();
    ~Logger();
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    std::ofstream logFile;
    std::mutex logMutex;
};
