cmake_minimum_required(VERSION 3.26)

project(1_1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./../bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY  ./../lib)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_MakeAvailable(googletest)

set(SOURCE_FILES
        src/stdafx.h
        src/main.cpp
        src/arithmetic-mean.cpp
        src/arithmetic-mean.h
)

set(TEST_SOURCE_FILES
        test/test.cpp
        src/arithmetic-mean.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

add_executable(${PROJECT_NAME}_test ${TEST_SOURCE_FILES})
target_link_libraries(${PROJECT_NAME}_test gtest_main)
enable_testing()
add_test(NAME ${PROJECT_NAME}_test COMMAND ${PROJECT_NAME}_test)