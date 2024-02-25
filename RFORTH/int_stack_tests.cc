#include <gtest/gtest.h>
#include "int_stack.h"
//initializing with capacity of 10
TEST(IntStackTest, Start) {
    int_stack_t stk;
    int_stack_init(&stk, 10);
    ASSERT_EQ(stk.size, 0);
    ASSERT_EQ(stk.capacity, 10);
}
//push/pop/get top element
TEST(IntStackTest, Push_Pop) {
    int_stack_t stk;
    int_stack_init(&stk, 10);
    int value;

    ASSERT_EQ(int_stack_push(&stk, 5), 1);
    ASSERT_EQ(stk.size, 1);
    ASSERT_EQ(int_stack_top(&stk, &value), 1);
    ASSERT_EQ(value, 5);
    ASSERT_EQ(int_stack_pop(&stk, &value), 1);
    ASSERT_EQ(value, 5);
    ASSERT_EQ(stk.size, 0);
}
//Swapping
TEST(IntStackTest, Swap_Two_Elems) {
    int_stack_t stk;
    int_stack_init(&stk, 10);
    int value1, value2;

    int_stack_push(&stk, 1);
    int_stack_push(&stk, 2);
    int_stack_swap(&stk);
    int_stack_pop(&stk, &value1);
    int_stack_pop(&stk, &value2);

    ASSERT_EQ(value1, 1);
    ASSERT_EQ(value2, 2);
}
//swap pairs
TEST(IntStackTest, SwapPairs) {
    int_stack_t stk;
    int_stack_init(&stk, 10);
    int value1, value2, value3, value4;

    int_stack_push(&stk, 1);
    int_stack_push(&stk, 2);
    int_stack_push(&stk, 3);
    int_stack_push(&stk, 4);
    int_stack_2swap(&stk);
    int_stack_pop(&stk, &value1);
    int_stack_pop(&stk, &value2);
    int_stack_pop(&stk, &value3);
    int_stack_pop(&stk, &value4);

    ASSERT_EQ(value1, 2);
    ASSERT_EQ(value2, 1);
    ASSERT_EQ(value3, 4);
    ASSERT_EQ(value4, 3);
}
//test for adding
TEST(IntStackTest, TestAdd) {
    int_stack_t stk;
    int_stack_init(&stk, 10);
    int value;

    int_stack_push(&stk, 3);
    int_stack_push(&stk, 4);
    int_stack_add(&stk);
    int_stack_pop(&stk, &value);

    ASSERT_EQ(value, 7);
}
//test for subbing
TEST(IntStackTest, Testsub) {
    int_stack_t stk;
    int_stack_init(&stk, 10);
    int value;

    int_stack_push(&stk, 10);
    int_stack_push(&stk, 4);
    int_stack_sub(&stk);
    int_stack_pop(&stk, &value);

    ASSERT_EQ(value, 6);
}
//test for mult
TEST(IntStackTest, TestMult) {
    int_stack_t stk;
    int_stack_init(&stk, 10);
    int value;

    int_stack_push(&stk, 3);
    int_stack_push(&stk, 4);
    int_stack_mult(&stk);
    int_stack_pop(&stk, &value);

    ASSERT_EQ(value, 12);
}
//test for div
TEST(IntStackTest, TestDiv) {
    int_stack_t stk;
    int_stack_init(&stk, 10);
    int value;

    int_stack_push(&stk, 12);
    int_stack_push(&stk, 4);
    int_stack_div(&stk);
    int_stack_pop(&stk, &value);

    ASSERT_EQ(value, 3);
}
//test for rot
TEST(IntStackTest, TestRot) {
    int_stack_t stk;
    int_stack_init(&stk, 10);
    int value1, value2, value3;

    int_stack_push(&stk, 1);
    int_stack_push(&stk, 2);
    int_stack_push(&stk, 3);
    int_stack_rot(&stk);
    int_stack_pop(&stk, &value1);
    int_stack_pop(&stk, &value2);
    int_stack_pop(&stk, &value3);

    ASSERT_EQ(value1, 1);
    ASSERT_EQ(value2, 3);
    ASSERT_EQ(value3, 2);
}
//test for drop
TEST(IntStackTest, TestDrop) {
    int_stack_t stk;
    int_stack_init(&stk, 10);
    int value;

    int_stack_push(&stk, 1);
    int_stack_push(&stk, 2);
    int_stack_drop(&stk);
    int_stack_pop(&stk, &value);

    ASSERT_EQ(value, 1);
    ASSERT_EQ(stk.size, 0);
}
//test for drop two
TEST(IntStackTest, DropTwoElems) {
    int_stack_t stk;
    int_stack_init(&stk, 10);

    int_stack_push(&stk, 1);
    int_stack_push(&stk, 2);
    int_stack_push(&stk, 3);
    int_stack_2drop(&stk);
    ASSERT_EQ(stk.size, 1);
}
//test for dup
TEST(IntStackTest, TestDup) {
    int_stack_t stk;
    int_stack_init(&stk, 10);
    int value1, value2;

    int_stack_push(&stk, 5);
    int_stack_dup(&stk);
    int_stack_pop(&stk, &value1);
    int_stack_pop(&stk, &value2);

    ASSERT_EQ(value1, 5);
    ASSERT_EQ(value2, 5);
}
//test for 2dup
TEST(IntStackTest, Dup_Two_Elems) {
    int_stack_t stk;
    int_stack_init(&stk, 10);
    int value1, value2, value3, value4;

    int_stack_push(&stk, 1);
    int_stack_push(&stk, 2);
    int_stack_2dup(&stk);
    int_stack_pop(&stk, &value1);
    int_stack_pop(&stk, &value2);
    int_stack_pop(&stk, &value3);
    int_stack_pop(&stk, &value4);

    ASSERT_EQ(value1, 2);
    ASSERT_EQ(value2, 1);
    ASSERT_EQ(value3, 2);
    ASSERT_EQ(value4, 1);
}
//test for over
TEST(IntStackTest, TestOver) {
    int_stack_t stk;
    int_stack_init(&stk, 10);
    int value1, value2, value3;

    int_stack_push(&stk, 1);
    int_stack_push(&stk, 2);
    int_stack_over(&stk);
    int_stack_pop(&stk, &value1);
    int_stack_pop(&stk, &value2);
    int_stack_pop(&stk, &value3);

    ASSERT_EQ(value1, 1);
    ASSERT_EQ(value2, 2);
    ASSERT_EQ(value3, 1);
}
//test for 2over
TEST(IntStackTest, Test2Over) {
    int_stack_t stk;
    int_stack_init(&stk, 10);
    int value1, value2, value3, value4, value5;

    int_stack_push(&stk, 1);
    int_stack_push(&stk, 2);
    int_stack_push(&stk, 3);
    int_stack_push(&stk, 4);
    int_stack_2over(&stk);
    int_stack_pop(&stk, &value1);
    int_stack_pop(&stk, &value2);
    int_stack_pop(&stk, &value3);
    int_stack_pop(&stk, &value4);
    int_stack_pop(&stk, &value5);

    ASSERT_EQ(value1, 3);  
    ASSERT_EQ(value2, 2);  
    ASSERT_EQ(value3, 4);
    ASSERT_EQ(value4, 3);
    ASSERT_EQ(value5, 2);
}

