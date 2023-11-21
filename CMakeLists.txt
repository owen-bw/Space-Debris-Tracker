cmake_minimum_required(VERSION 3.5.0)

project(space-debris-tracker VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(glfw3 REQUIRED)

file(GLOB_RECURSE SOURCES "src/*.cpp" "src/gl.c")

add_executable(space-debris-tracker ${SOURCES})

target_include_directories(space-debris-tracker PRIVATE include)

target_link_libraries(space-debris-tracker glfw "-framework Cocoa" "-framework OpenGL" "-framework IOKit" "-lc++")

add_custom_command(
    TARGET space-debris-tracker
    POST_BUILD
    COMMAND ./space-debris-tracker
)