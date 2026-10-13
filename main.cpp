#include <dpp/dpp.h>
#include <iostream>
#include <cstdlib>
#include "ai_brain.hpp"
#include "logger.hpp"

int main() {
    const char* token = std::getenv("DISCORD_TOKEN");
    if (!token) {
        Logger::log("ERROR", "DISCORD_TOKEN is missing!");
        return 1;
    }

    dpp::cluster bot(token, dpp::i_default_intents | dpp::i_message_content);

    bot.on_log([](const dpp::log_t& event) {
        Logger::log("DPP", event.message);
    });

    bot.on_message_create([&bot](const dpp::message_create_t& event) {
        if (event.msg.author.is_bot()) return;

        Logger::log("INFO", "Received message from user: " + event.msg.content);
        std::string reply = AiBrain::getResponse(event.msg.content);
        bot.message_create(dpp::message(event.msg.channel_id, reply));
    });

    bot.on_ready([&bot](const dpp::ready_t& event) {
        Logger::log("INFO", "Successfully logged in as: " + bot.me.username);
    });

    Logger::log("INFO", "Starting ShawarmaAi bot...");
    bot.start(dpp::st_wait);
    return 0;
}