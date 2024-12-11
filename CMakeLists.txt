cmake_minimum_required(VERSION 3.21)
project(test_c C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -save-temps=obj")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -save-temps=obj")

include_directories(
        common
        common/algorithm
        common/framework
        common/framework/oop
        common/framework/oop/oop_usage
        common/structure
        game
        modules
)

file(
        GLOB_RECURSE SOURCES
        "common/algorithm/*.c"
        "common/framework/*.c"
        "common/framework/oop/oop_usage/*.c"
        "common/framework/oop/oop_usage/class_demo/*.c"
        "common/framework/oop/oop_usage/class_demo_base/*.c"
        "common/structure/*.c"
        "common/*.c"
        "game/*.c"
        "modules/*.c"
)

add_executable(test_c main.c ${SOURCES})
