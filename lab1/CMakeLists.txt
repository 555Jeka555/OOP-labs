cmake_minimum_required(VERSION 3.26)
project(lab1)

set(CMAKE_CXX_STANDARD 17)

add_executable(lab1 main.cpp)

add_executable(replace 1-4/replace.cpp
        1-4/stdafx.h)

add_executable(radix 2-6/radix.cpp
        2-6/stdafx.h)

add_executable(invert 3-2/invert.cpp
        3-2/stdafx.h
        4-3/crypt.cpp)

add_executable(crypt 4-3/crypt.cpp
        4-3/stdafx.h
        4-3/crypt.cpp)

set_target_properties(replace PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/1-4/replace")

set_target_properties(replace PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/2-6/radix")

set_target_properties(replace PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/3-2/invert")

add_custom_command(
        TARGET invert
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E echo "Running post-build script"
        COMMAND "${CMAKE_CURRENT_SOURCE_DIR}/3-2/test.bat"
        COMMENT "Running post-build script"
        DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/3-2/invert.cpp"  # �������� ����������� �� .cpp �����
)

set_target_properties(replace PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/4-3/crypt")