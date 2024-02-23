#include <gtest/gtest.h>
#include "int_stack.h"

TEST(IntStackTest, Initialization) {
    int_stack_t stk;
    int_stack_init(&stk, 10);
    ASSERT_EQ(stk.size, 0);
    ASSERT_EQ(stk.capacity, 10);
}

TEST(IntStackTest, PushPopTop) {
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

TEST(IntStackTest, Swap) {
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

TEST(IntStackTest, TwoSwap) {
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

TEST(IntStackTest, Add) {
    int_stack_t stk;
    int_stack_init(&stk, 10);
    int value;

    int_stack_push(&stk, 3);
    int_stack_push(&stk, 4);
    int_stack_add(&stk);
    int_stack_pop(&stk, &value);

    ASSERT_EQ(value, 7);
}

TEST(IntStackTest, Sub) {
    int_stack_t stk;
    int_stack_init(&stk, 10);
    int value;

    int_stack_push(&stk, 10);
    int_stack_push(&stk, 4);
    int_stack_sub(&stk);
    int_stack_pop(&stk, &value);

    ASSERT_EQ(value, 6);
}

TEST(IntStackTest, Mult) {
    int_stack_t stk;
    int_stack_init(&stk, 10);
    int value;

    int_stack_push(&stk, 3);
    int_stack_push(&stk, 4);
    int_stack_mult(&stk);
    int_stack_pop(&stk, &value);

    ASSERT_EQ(value, 12);
}

TEST(IntStackTest, Div) {
    int_stack_t stk;
    int_stack_init(&stk, 10);
    int value;

    int_stack_push(&stk, 12);
    int_stack_push(&stk, 4);
    int_stack_div(&stk);
    int_stack_pop(&stk, &value);

    ASSERT_EQ(value, 3);
}

TEST(IntStackTest, Rot) {
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

TEST(IntStackTest, Drop) {
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

TEST(IntStackTest, TwoDrop) {
    int_stack_t stk;
    int_stack_init(&stk, 10);

    int_stack_push(&stk, 1);
    int_stack_push(&stk, 2);
    int_stack_push(&stk, 3);
    int_stack_2drop(&stk);
    ASSERT_EQ(stk.size, 1);
}

TEST(IntStackTest, Dup) {
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

TEST(IntStackTest, TwoDup) {
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

TEST(IntStackTest, Over) {
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

TEST(IntStackTest, TwoOver) {
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

    ASSERT_EQ(value1, 2);
    ASSERT_EQ(value2, 1);
    ASSERT_EQ(value3, 4);
    ASSERT_EQ(value4, 3);
    ASSERT_EQ(value5, 2);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
