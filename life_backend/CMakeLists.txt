cmake_minimum_required(VERSION 3.26)
project(game)
#
#include(FetchContent)
#FetchContent_Declare(
#        googletest
#        GIT_REPOSITORY https://github.com/google/googletest.git
#        GIT_TAG        release-1.12.0
#)
#FetchContent_MakeAvailable(googletest)

set(CMAKE_CXX_STANDARD 23)
#set(TEST_NAME ${PROJECT_NAME}_tests)
add_executable(${PROJECT_NAME}_bin Life.h Life.cpp ../main.cpp)

#add_executable(${TEST_NAME}
#        Life.cpp
#        Life.h
#        life_test/life_tets.cpp)

#target_link_libraries(${TEST_NAME} gtest_main)
#
#enable_testing()
#include(GoogleTest)
#gtest_discover_tests(${TEST_NAME})
