cmake_minimum_required(VERSION 3.14)
project(life_backend)

set(CMAKE_CXX_STANDARD 23)

set(SOURCES
        Life.cpp
)

set(HEADERS
        Life.h
)

if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    add_library(${PROJECT_NAME} STATIC Life.cpp)
else ()
    add_library(${PROJECT_NAME} SHARED Life.cpp)
endif ()