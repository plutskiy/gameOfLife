cmake_minimum_required(VERSION 3.14)
project(life_frontend)

set(CMAKE_CXX_STANDARD 23)
set(DYNAMIC_LIBS_PATH ${CMAKE_SOURCE_DIR})

if (CMAKE_SYSTEM_PROCESSOR STREQUAL "arm64")
    message(STATUS "Target architecture: ARM")
    set(ARCH "arm64")
elseif (CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64")
    message(STATUS "Target architecture: x86_64 (x64)")
    set(ARCH "x86_64")
elseif (CMAKE_SYSTEM_PROCESSOR STREQUAL "AMD64")
    message(STATUS "Target architecture: x86_64 (x64)")
    set(ARCH "x86_64")
elseif (CMAKE_SYSTEM_PROCESSOR STREQUAL "x86")
    message(STATUS "Target architecture: x86")
    set(ARCH "x86")
else ()
    message(FATAL_ERROR "Unsupported architecture: ${CMAKE_SYSTEM_PROCESSOR}")
endif ()

add_executable(${PROJECT_NAME} life_frontend.h life_frontend.cpp ../life_backend/Life.h ../life_backend/Life.cpp)
cmake_path(APPEND SDL_INCLUDE_PATH "${CMAKE_SOURCE_DIR}" "libraries" "include")
message(STATUS "Path to SDL includes: ${SDL_INCLUDE_PATH}")
target_include_directories(${PROJECT_NAME} BEFORE PUBLIC ${SDL_INCLUDE_PATH})
target_link_libraries(${PROJECT_NAME} life_backend)
include_directories(${PROJECT_NAME} ${SDL_INCLUDE_PATH})
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    set(CURRENT_OS "Linux")
    set(CURRENT_EXT "so")
    set(MY_VARIABLE "SDL2.${CURRENT_EXT}")
    cmake_path(APPEND SDL_PATH_FULL "${CMAKE_SOURCE_DIR}" "libraries" "${ARCH}" "${CURRENT_OS}" "SDL2.${CURRENT_EXT}")
    add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy ${SDL_PATH_FULL} ${CMAKE_BINARY_DIR}
            COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/logo.png ${CMAKE_CURRENT_BINARY_DIR}
    )
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/info.desktop.in ${CMAKE_CURRENT_BINARY_DIR}/info.desktop)
    file(COPY ${CMAKE_CURRENT_BINARY_DIR}/info.desktop DESTINATION $ENV{HOME}/.local/share/applications/)
elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    set(CURRENT_OS "Windows")
    set(CURRENT_EXT "dll")
    set(MY_VARIABLE "SDL2.${CURRENT_EXT}")
    cmake_path(APPEND SDL_PATH_FULL "${CMAKE_SOURCE_DIR}" "libraries" "${ARCH}" "${CURRENT_OS}" "SDL2.${CURRENT_EXT}")
    add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy ${SDL_PATH_FULL} ${CMAKE_CURRENT_BINARY_DIR}
    )
    target_sources(${PROJECT_NAME} PRIVATE info.rc)
    set_target_properties(${PROJECT_NAME} PROPERTIES
            WIN32_EXECUTABLE TRUE
    )
elseif (CMAKE_CXX_COMPILER_ID MATCHES "AppleClang")
    set(CURRENT_OS "macOS")
    set(CURRENT_EXT "dylib")
    set(BACKEND_PATH ${CMAKE_SOURCE_DIR}/cmake-build-debug/life_backend/liblife_backend.${CURRENT_EXT})
    set(MY_VARIABLE "SDL2.${CURRENT_EXT}")
    cmake_path(APPEND SDL_PATH_FULL "${CMAKE_SOURCE_DIR}" "libraries" "${ARCH}" "${CURRENT_OS}" "SDL2.${CURRENT_EXT}")
    set(DYLIB_DESTINATION $<TARGET_BUNDLE_DIR:${PROJECT_NAME}>/Contents/Frameworks/${MY_VARIABLE})
    add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy ${SDL_PATH_FULL} ${DYLIB_DESTINATION}
    )
    add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_BUNDLE_DIR:${PROJECT_NAME}>/Contents/Frameworks/
            COMMAND ${CMAKE_COMMAND} -E copy ${BACKEND_PATH} $<TARGET_BUNDLE_DIR:${PROJECT_NAME}>/Contents/Frameworks/
    )
    add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_BUNDLE_DIR:${PROJECT_NAME}>/Contents/Resources/
            COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/logo.png $<TARGET_BUNDLE_DIR:${PROJECT_NAME}>/Contents/Resources/
            COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/Info.plist $<TARGET_BUNDLE_DIR:${PROJECT_NAME}>/
    )
    message(STATUS "SDL full path directory: ${SDL_PATH_FULL}")
    set_target_properties(${PROJECT_NAME} PROPERTIES
            MACOSX_BUNDLE TRUE
            MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/Info.plist
            RESOURCES "${SDL_PATH_FULL}"
    )
else ()
    message(FATAL_ERROR "Unsupported compiler: ${CMAKE_CXX_COMPILER_ID}")
endif ()

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/variables.h.in ${CMAKE_CURRENT_SOURCE_DIR}/variables.h)

