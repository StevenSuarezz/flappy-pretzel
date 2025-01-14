cmake_minimum_required(VERSION 3.10)
project(FlappyPretzel)

if(APPLE)
    include_directories(/opt/homebrew/include)
    link_directories(/opt/homebrew/lib)
endif()

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)

add_executable(game src/main.c)
target_link_libraries(game SDL2::SDL2 SDL2_image::SDL2_image SDL2_mixer::SDL2_mixer)
