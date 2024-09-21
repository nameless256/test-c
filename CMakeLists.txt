cmake_minimum_required(VERSION 3.21)
project(test_c C)

set(CMAKE_C_STANDARD 11)

include_directories(common)
include_directories(common/algorithm)
include_directories(common/structure)
include_directories(game)
include_directories(modules)

file(
        GLOB_RECURSE SOURCES
        "modules/*.c"
        "common/*.c"
#        "common/structure/*.c"
        "game/*.c"
)

add_executable(test_c main.c ${SOURCES})
