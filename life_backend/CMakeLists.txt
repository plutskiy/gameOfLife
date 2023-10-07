cmake_minimum_required(VERSION 3.26)
project(game)

set(CMAKE_CXX_STANDARD 23)
add_executable(${PROJECT_NAME}_bin Life.h Life.cpp ../main.cpp)
