cmake_minimum_required(VERSION 3.10)
project(SmartDiscordBot)

# Set C++ 17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Tell CMake to build an executable named 'discord-bot' from main.cpp
add_executable(discord-bot main.cpp)