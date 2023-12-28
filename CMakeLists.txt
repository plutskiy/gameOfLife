cmake_minimum_required(VERSION 3.14)
project(game_of_life)
set(CMAKE_CXX_STANDARD 23)

add_subdirectory(life_backend)
add_subdirectory(life_frontend)
add_subdirectory(life_test)