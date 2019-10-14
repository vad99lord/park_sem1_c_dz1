#include "Stack.h"
#include <stdio.h>
#include <stdlib.h>
#include "Point.h"

// Driver program to test Stack functions
int main() {
    Stack *stack = create_stack(sizeof(Point));
    if (isEmpty(stack))
        printf("Can't pop from empty stack\n");
    int *values = malloc(6 * sizeof(int));
    for (int i = 0; i < 6; i++) {
        values[i] = i;
    }
    int *iter = values;
    Point val1 = {iter, iter++};
    Point val2 = {iter, iter++};
    Point val3 = {iter, iter++};
    push(stack, &val1);
    push(stack, &val2);
    push(stack, &val3);
    Point point;
    pop(stack, &point);
    printf("%d popped from stack\n", *point.x);
    pop(stack, &point);
    printf("%d popped from stack\n", *point.y);
    printf("%d stack\n", *((Point *) peek(stack))->y);
    pop(stack, &point);
    printf("%d popped from stack\n", *point.x);
    printf("%d popped from stack\n", isEmpty(stack));
    delete_stack(stack);
    free(values);

    stack = create_stack(sizeof(int));
    int popped = 0;
    int a = 1, b = 2, c = 3;
    push(stack, &a);
    push(stack, &b);
    pop(stack, &popped);
    printf("%d popped from stack\n", popped);
    push(stack, &c);
    pop(stack, &popped);
    printf("%d popped from stack\n", popped);
    pop(stack, &popped);
    printf("%d popped from stack\n", popped);
    pop(stack, &popped);
    printf("%d popped from stack\n", popped);
    delete_stack(stack);
    return 0;
}

