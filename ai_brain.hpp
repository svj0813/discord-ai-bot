#pragma once
#include <string>
#include <algorithm>

class AiBrain {
public:
    static std::string getResponse(std::string message) {
        // Convert message to lowercase for easy matching
        std::transform(message.begin(), message.end(), message.begin(), ::tolower);

        if (message.find("hello") != std::string::npos || message.find("hi") != std::string::npos) {
            return "Hello! I am ShawarmaAi, your custom C++ assistant. 🌯";
        }
        else if (message.find("how are you") != std::string::npos) {
            return "Running smoothly on Fedora and powered by custom C++ logic!";
        }
        else if (message.find("code") != std::string::npos || message.find("project") != std::string::npos) {
            return "This bot is modularized with custom C++ headers and the D++ library!";
        }
        else if (message.find("help") != std::string::npos) {
            return "I can respond to greetings, chat about my code, or reply to !ping!";
        }
        
        return "That's interesting! Tell me more, or type 'help' to see what I can do.";
    }
};