cmake_minimum_required(VERSION 3.16)
project(RFORTH)

# Set C standard
set(CMAKE_C_STANDARD 11)

# Include directories
include_directories(${PROJECT_SOURCE_DIR})

# Add the int_stack library
add_library(int_stack_lib
    int_stack.c
    int_stack.h
    token.c   # Add this line
    token.h   # Add this line if you have a token.h file
)

# Add the main RFORTH executable
add_executable(rforth
    main.c
)
target_link_libraries(rforth
    int_stack_lib
)

# GoogleTest integration for unit testing
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
)
FetchContent_MakeAvailable(googletest)

# Add the GoogleTest-based test executable
enable_testing()
add_executable(googletest
    int_stack_tests.cc
)
target_link_libraries(googletest
    int_stack_lib
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(googletest)
