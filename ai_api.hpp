#pragma once
#include <string>
#include <curl/curl.h>
#include "logger.hpp"

class AiApi {
public:
    static void init() {
        curl_global_init(CURL_GLOBAL_DEFAULT);
        Logger::log("INFO", "CURL globally initialized for future AI calls. 🌐");
    }

    static void cleanup() {
        curl_global_cleanup();
    }
};