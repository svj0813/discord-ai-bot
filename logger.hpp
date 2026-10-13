#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <iomanip>

class Logger {
public:
    static void log(const std::string& level, const std::string& message) {
        // Get current timestamp
        auto now = std::chrono::system_clock::now();
        auto in_time_t = std::chrono::system_clock::to_time_t(now);

        std::stringstream ss;
        ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %H:%M:%S");
        
        std::string logEntry = "[" + ss.str() + "] [" + level + "] " + message;

        // Print to console
        std::cout << logEntry << std::endl;

        // Append to bot.log file
        std::ofstream logFile("bot.log", std::ios_base::app);
        if (logFile.is_open()) {
            logFile << logEntry << std::endl;
        }
    }
};  