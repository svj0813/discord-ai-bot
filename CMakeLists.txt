cmake_minimum_required(VERSION 3.13)
project(ShawarmaBot)

# Set C++ 17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Fetch the D++ library automatically
include(FetchContent)
FetchContent_Declare(
    dpp
    GIT_REPOSITORY https://github.com/brainboxdotcc/DPP.git
    GIT_TAG v10.0.35
)
FetchContent_MakeAvailable(dpp)

# Find libcurl package for future AI API requests
find_package(CURL REQUIRED)

# Build the executable
add_executable(discord-bot main.cpp)

# Link D++ and CURL libraries
target_link_libraries(discord-bot PRIVATE dpp CURL::libcurl)