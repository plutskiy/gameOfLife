cmake_minimum_required(VERSION 3.14)
project(life_backend)

set(CMAKE_CXX_STANDARD 23)

set(SOURCES
        Life.cpp
)

set(HEADERS
        Life.h
)

add_library(${PROJECT_NAME} SHARED Life.cpp)