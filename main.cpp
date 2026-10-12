#include <dpp/dpp.h>
#include <iostream>
#include <cstdlib>

int main() {
    const char* token = std::getenv("DISCORD_TOKEN");
    if (!token) {
        std::cerr << "Error: DISCORD_TOKEN is missing!" << std::endl;
        return 1;
    }

    // Initialize bot with default intents and explicit message content intent
    dpp::cluster bot(token, dpp::i_default_intents | dpp::i_message_content);

    bot.on_log(dpp::utility::cout_logger());

    bot.on_message_create([&bot](const dpp::message_create_t& event) {
        if (event.msg.content == "!ping" && !event.msg.author.is_bot()) {
            bot.message_create(dpp::message(event.msg.channel_id, "Pong! 🌯"));
        }
    });

    bot.on_ready([&bot](const dpp::ready_t& event) {
        std::cout << "Success! Logged in as: " << bot.me.username << std::endl;
    });

    bot.start(dpp::st_wait);
    return 0;
}   