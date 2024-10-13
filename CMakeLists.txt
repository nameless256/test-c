cmake_minimum_required(VERSION 3.21)
project(test_c C)

set(CMAKE_C_STANDARD 11)

include_directories(
        common
        common/algorithm
        common/framework
        common/structure
        game
        modules
)

file(
        GLOB_RECURSE SOURCES
        "common/algorithm/*.c"
        "common/framework/*.c"
        "common/structure/*.c"
        "common/*.c"
        "game/*.c"
        "modules/*.c"
)

add_executable(test_c main.c ${SOURCES})
