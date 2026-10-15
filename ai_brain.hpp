#pragma once
#include <string>
#include "logger.hpp"
#include "ai_api.hpp"

class AiBrain {
public:
    static std::string getResponse(const std::string& input) {
        if (input == "!ping") return "Pong!";
        if (input == "!info") return "I am ShawarmaAi, a C++ intelligent bot.";

        Logger::log("INFO", "Routing prompt to Groq Llama 3...");
        return AiApi::askLLM(input);
    }
};