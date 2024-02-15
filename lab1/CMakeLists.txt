cmake_minimum_required(VERSION 3.26)
project(lab1)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab1 main.cpp)
add_executable(2-6 2-6/radix.cpp)
add_executable(replace 1-4/replace.cpp
        1-4/stdafx.h)

set_target_properties(replace PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/1-4/replace")
