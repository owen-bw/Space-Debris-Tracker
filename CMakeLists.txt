cmake_minimum_required(VERSION 3.5.0)

project(space-debris-tracker VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(WIN32)
    set(GLFW_DIR "${CMAKE_SOURCE_DIR}/lib/windows")
elseif(APPLE)
    set(MACOS_LIBRARIES ...)
elseif(UNIX AND NOT APPLE)
    set(UNIX_LIBRARIES ...)
endif()

file(GLOB_RECURSE SOURCES "src/*.cpp" "src/gl.c")

add_executable(space-debris-tracker ${SOURCES})

target_include_directories(space-debris-tracker PRIVATE include)

if(WIN32)
    find_library(GLFW_LIBRARY NAMES glfw3 PATHS ${GLFW_DIR})
    target_link_libraries(space-debris-tracker ${GLFW_LIBRARY})
    target_link_libraries(space-debris-tracker opengl32)
elseif(APPLE)
    target_link_libraries(space-debris-tracker glfw "-framework Cocoa" "-framework OpenGL" "-framework IOKit" "-lc++")
elseif(UNIX AND NOT APPLE)
    set(UNIX_LIBRARIES ...)
endif()

add_custom_command(
    TARGET space-debris-tracker
    POST_BUILD
    COMMAND ./space-debris-tracker
)