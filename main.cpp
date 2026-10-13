#include <dpp/dpp.h>
#include <iostream>
#include <cstdlib>
#include "ai_brain.hpp"

int main() {
    const char* token = std::getenv("DISCORD_TOKEN");
    if (!token) {
        std::cerr << "Error: DISCORD_TOKEN is missing!" << std::endl;
        return 1;
    }

    dpp::cluster bot(token, dpp::i_default_intents | dpp::i_message_content);

    bot.on_log(dpp::utility::cout_logger());

    bot.on_message_create([&bot](const dpp::message_create_t& event) {
        if (event.msg.author.is_bot()) return;

        if (event.msg.content == "!ping") {
            bot.message_create(dpp::message(event.msg.channel_id, "Pong! 🌯"));
        } 
        else {
            std::string reply = AiBrain::getResponse(event.msg.content);
            bot.message_create(dpp::message(event.msg.channel_id, reply));
        }
    });

    bot.on_ready([&bot](const dpp::ready_t& event) {
        std::cout << "Success! Logged in as: " << bot.me.username << std::endl;
    });

    bot.start(dpp::st_wait);
    return 0;
}