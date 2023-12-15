cmake_minimum_required(VERSION 3.24)
project(game_of_life)
set(CMAKE_CXX_STANDARD 23)

#set(SDL2_LIBRARY "${CMAKE_BINARY_DIR}/SDL2.dll")
#set(SDL2_INCLUDE_DIR "SDL2-2.28.4/x86_64-w64-mingw32/include/SDL2")
#
#IF(MINGW)
#    SET(MINGW32_LIBRARY mingw32 "-mwindows" CACHE STRING "mwindows for MinGW")
#ENDIF(MINGW)
#IF(NOT APPLE)
#    FIND_PACKAGE(Threads)
#    SET(SDL2_LIBRARY_TEMP ${SDL2_LIBRARY_TEMP} ${CMAKE_THREAD_LIBS_INIT})
#ENDIF(NOT APPLE)
#
#IF(MINGW)
#    SET(SDL2_LIBRARY_TEMP ${MINGW32_LIBRARY} ${SDL2_LIBRARY_TEMP})
#ENDIF(MINGW)
#IF(MINGW)
#    SET(SDL2_LIBRARY_TEMP mingw32 SDL2 -mwindows)
#ENDIF(MINGW)

add_executable(game_of_life life_frontend/life_frontend.cpp)
target_link_libraries(game_of_life life_backend)
add_subdirectory(life_backend)
add_subdirectory(life_frontend)
add_subdirectory(life_test)

