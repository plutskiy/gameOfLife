cmake_minimum_required(VERSION 3.26)
project(game)

set(CMAKE_CXX_STANDARD 23)

include_directories("${PROJECT_SOURCE_DIR}/life_tests")
add_subdirectory(life_tests)
include_directories("${PROJECT_SOURCE_DIR}/life_backend/cmake-build-debug")
add_subdirectory(life_backend)
include_directories("${PROJECT_SOURCE_DIR}/life_frontend")
add_subdirectory(life_frontend)

add_executable(${PROJECT_NAME}_bin main.cpp)