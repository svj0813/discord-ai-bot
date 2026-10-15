#pragma once
#include <string>
#include <cstdlib>
#include <curl/curl.h>
#include <dpp/dpp.h>
#include "logger.hpp"

// Callback function required by CURL to write incoming HTTP response chunks
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    size_t total_size = size * nmemb;
    ((std::string*)userp)->append((char*)contents, total_size);
    return total_size;
}

class AiApi {
public:
    static void init() {
        curl_global_init(CURL_GLOBAL_DEFAULT);
        Logger::log("INFO", "CURL globally initialized for API calls. 🌐");
    }

    static void cleanup() {
        curl_global_cleanup();
    }

    static std::string askLLM(const std::string& prompt) {
        const char* apiKey = std::getenv("GROQ_API_KEY");
        if (!apiKey) {
            Logger::log("ERROR", "GROQ_API_KEY missing from environment variables.");
            return "Error: Brain disconnected (GROQ_API_KEY missing).";
        }

        CURL* curl = curl_easy_init();
        if (!curl) return "Error: Failed to initialize network request.";

        std::string readBuffer;

        // Construct JSON request body for Groq API
        nlohmann::json jsonPayload = {
            {"model", "llama-3.3-70b-versatile"},
            {"messages", {{{"role", "user"}, {"content", prompt}}}}
        };
        std::string payloadStr = jsonPayload.dump();

        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        std::string authHeader = std::string("Authorization: Bearer ") + apiKey;
        headers = curl_slist_append(headers, authHeader.c_str());

        curl_easy_setopt(curl, CURLOPT_URL, "https://api.groq.com/openai/v1/chat/completions");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payloadStr.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        CURLcode res = curl_easy_perform(curl);
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);

        if (res != CURLE_OK) {
            Logger::log("ERROR", std::string("CURL request failed: ") + curl_easy_strerror(res));
            return "Error: Network request to Groq API failed.";
        }

        try {
            nlohmann::json responseJson = nlohmann::json::parse(readBuffer);
            if (responseJson.contains("choices") && !responseJson["choices"].empty()) {
                return responseJson["choices"][0]["message"]["content"];
            } else if (responseJson.contains("error")) {
                std::string errStr = responseJson["error"]["message"];
                Logger::log("ERROR", "Groq API error: " + errStr);
                return "Groq API Error: " + errStr;
            }
            return "Error: Unexpected response structure from Groq.";
        } catch (const std::exception& e) {
            Logger::log("ERROR", std::string("Failed to parse Groq JSON response: ") + e.what());
            return "Error: Received unreadable response from Groq.";
        }
    }
};