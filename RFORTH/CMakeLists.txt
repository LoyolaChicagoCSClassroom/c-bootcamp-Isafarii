
enable_testing()

add_library(int_stack_lib
    int_stack.c
    int_stack.h
)

add_executable(googletest
    int_stack_tests.cc
)

target_link_libraries(googletest
    int_stack_lib  
    gtest_main
    gtest
)


add_test(NAME int_stack_tests COMMAND googletest)
