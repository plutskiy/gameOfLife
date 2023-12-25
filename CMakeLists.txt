cmake_minimum_required(VERSION 3.24)
project(game_of_life)
set(CMAKE_CXX_STANDARD 23)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(game_of_life life_frontend/life_frontend.cpp)
target_link_libraries(game_of_life ${SDL2_LIBRARIES} life_backend)
add_subdirectory(life_backend)
add_subdirectory(life_frontend)
add_dependencies(game_of_life life_frontend)  # Add this line
add_subdirectory(life_test)