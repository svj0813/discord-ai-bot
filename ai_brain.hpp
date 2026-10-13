#pragma once
#include <string>
#include <algorithm>
#include <sstream>
#include <chrono>

class AiBrain {
private:
    // Record bot startup time when the class initializes
    inline static const std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();

public:
    static std::string handleCommand(const std::string& content) {
        if (content.empty()) return "";

        if (content[0] == '!') {
            std::stringstream ss(content);
            std::string cmd;
            ss >> cmd;

            if (cmd == "!info") {
                return "ShawarmaAi v1.1 | Built with C++ and D++ library on Fedora Linux. 🚀";
            }
            else if (cmd == "!echo") {
                std::string arg;
                std::getline(ss, arg);
                if (!arg.empty() && arg[0] == ' ') arg.erase(0, 1);
                return arg.empty() ? "Usage: !echo <message>" : arg;
            }
            else if (cmd == "!uptime") {
                auto now = std::chrono::steady_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::seconds>(now - startTime).count();
                
                long hours = duration / 3600;
                long minutes = (duration % 3600) / 60;
                long seconds = duration % 60;

                return "⏳ Uptime: " + std::to_string(hours) + "h " + 
                       std::to_string(minutes) + "m " + 
                       std::to_string(seconds) + "s";
            }
        }
        return ""; 
    }

    static std::string getResponse(std::string message) {
        std::string cmdResponse = handleCommand(message);
        if (!cmdResponse.empty()) {
            return cmdResponse;
        }

        std::string lowerMsg = message;
        std::transform(lowerMsg.begin(), lowerMsg.end(), lowerMsg.begin(), ::tolower);

        if (lowerMsg.find("hello") != std::string::npos || lowerMsg.find("hi") != std::string::npos) {
            return "Hello! I am ShawarmaAi, your custom C++ assistant. 🌯";
        }
        else if (lowerMsg.find("how are you") != std::string::npos) {
            return "Running smoothly on Fedora and powered by modular C++ logic!";
        }
        else if (lowerMsg.find("code") != std::string::npos || lowerMsg.find("project") != std::string::npos) {
            return "This bot is modularized with custom C++ headers and the D++ library!";
        }
        else if (lowerMsg.find("help") != std::string::npos) {
            return "Commands: !ping, !info, !echo <text>, !uptime. Or just chat with me!";
        }
        
        return "That's interesting! Tell me more, or type 'help' to see what I can do.";
    }
};