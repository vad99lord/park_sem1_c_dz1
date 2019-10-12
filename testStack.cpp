#include <gtest/gtest.h>

//extern "C" {
#include "max_area.h"
#include "Stack.h"
#include "Point.h"
//}


TEST(StackTests, IntegerTest) {
    Stack *stack = create_stack(sizeof(int));
    ASSERT_TRUE(isEmpty(stack));
    int popped = 0;
    int a = 1, b = 2, c = 3;
    push(stack, &a);
    push(stack, &b);
    pop(stack, &popped);
    ASSERT_EQ(popped, 2);
    push(stack, &c);
    pop(stack, &popped);
    ASSERT_TRUE(!isEmpty(stack));
    ASSERT_EQ(popped, 3);
    pop(stack, &popped);
    ASSERT_EQ(popped, 1);
    popped = -100;
    EXPECT_EQ(popped, -100);
    ASSERT_TRUE(isEmpty(stack));
    ASSERT_EQ(peek(stack), nullptr);
    delete_stack(stack);
}


TEST(StackTests, PointTest) {
    Stack *stack = create_stack(sizeof(Point));
    int size = 3;
    int *values = new int[3];
    for (int i = 0; i < 3; i++) {
        values[i] = i;
    }
    int *iter = values;
    Point val1 = {iter, iter++};
    Point val2 = {iter, iter++};
    Point val3 = {iter, iter++};
    ASSERT_TRUE(isEmpty(stack));
    Point popped;
    push(stack, &val1);
    pop(stack, &popped);
    ASSERT_EQ(*popped.x, 0);
    push(stack, &val3);
    ASSERT_TRUE(!isEmpty(stack));
    push(stack, &val2);
    pop(stack, &popped);
    ASSERT_EQ(*popped.y, 1);
    popped = *(Point *) peek(stack);
    ASSERT_EQ(*popped.x, 2);
    delete_stack(stack);
    delete[] values;
}
