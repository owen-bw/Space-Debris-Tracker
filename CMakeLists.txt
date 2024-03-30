cmake_minimum_required(VERSION 3.5.0)

project(space-debris-tracker VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(WIN32)
    link_directories(${CMAKE_SOURCE_DIR}/lib/windows)
    find_library(GLFW_LIBRARY NAMES glfw3 PATHS ${CMAKE_SOURCE_DIR}/lib/windows)
elseif(APPLE)
    link_directories(${CMAKE_SOURCE_DIR}/lib/mac)
    find_package(glfw3 REQUIRED)
endif()

file(GLOB_RECURSE SOURCES "src/*.cpp" "src/gl.c" "include/tle/*.c")

add_executable(space-debris-tracker ${SOURCES})

target_include_directories(space-debris-tracker PRIVATE include)

if(WIN32)
    target_link_libraries(space-debris-tracker ${GLFW_LIBRARY} opengl32)
elseif(APPLE)
    target_link_libraries(space-debris-tracker glfw "-framework Cocoa" "-framework OpenGL" "-framework IOKit")
endif()

add_custom_command(
    TARGET space-debris-tracker
    POST_BUILD
    COMMAND ./space-debris-tracker
)
