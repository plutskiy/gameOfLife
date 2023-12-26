cmake_minimum_required(VERSION 3.24)
project(game_of_life)
set(CMAKE_CXX_STANDARD 23)

set(SDL_INCLUDE_PATH "${CMAKE_SOURCE_DIR}/libraries/include")

add_executable(game_of_life life_frontend/life_frontend.cpp)
target_include_directories(game_of_life BEFORE PUBLIC ${SDL_INCLUDE_PATH})
target_link_libraries(game_of_life ${SDL2_LIBRARIES} life_backend)

add_subdirectory(life_backend)
add_subdirectory(life_frontend)
add_dependencies(game_of_life life_frontend)
add_subdirectory(life_test)