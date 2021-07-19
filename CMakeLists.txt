cmake_minimum_required(VERSION 3.14...3.20)

project(minishell C)

# set(CMAKE_BUILD_TYPE Release)
set(CMAKE_BUILD_TYPE Debug)

# Custom cmake modules
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
# Configure wether libraries will be static or shared linked
set(BUILD_SHARED_LIBS OFF)

# Determine minimum C
set(CMAKE_C_STANDARD 11)

# Show all warning messages
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

# Source files
add_subdirectory(src)

enable_testing()

add_subdirectory(tests)
