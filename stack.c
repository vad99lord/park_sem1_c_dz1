// C program for array implementation of stack
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "stack.h"

struct Stack {
    void *array; //container for elements
    size_t count; //number of elements in stack
    size_t capacity; //length of array
    size_t size; //size of 1 elem
};

// create empty stack, elem size is size of 1 element in stack
Stack *create_stack(size_t size) {
    Stack *stack = malloc(sizeof(Stack));
    stack->count = 0;
    stack->capacity = 2;
    stack->size = size;
    stack->array = malloc(stack->capacity * size);
    return stack;
}


//free memory connected with stack
void delete_stack(Stack *stack) {
    free(stack->array);
    free(stack);
}

// Check if stack is empty
bool isEmpty(const Stack *stack) {
    return stack->count == 0;
}

// Returns the number of items in the stack.
int stack_size(const Stack *stack) {
    return stack->count;
}

// private resize the array holding the elements
static void resize(size_t capacity, Stack *stack) {
    assert (capacity >= stack->count);

    void *temp = malloc(capacity * stack->size);
    stack->capacity = capacity;

    memcpy(temp, stack->array, stack->count * stack->size);
    //free previous array memory
    free(stack->array);
    stack->array = temp;
}

// Function to add an item to stack.
void push(Stack *stack, void *item) {
    if (stack->count == stack->capacity) {
        // double size of array if necessary
        resize((stack->capacity) * 2, stack);
    }
    //stack->array[stack->count++] = item;
    memcpy(&((char *) stack->array)[stack->count * stack->size], item, stack->size);
    stack->count++;
}

// Function to remove an item from stack
void pop(Stack *stack, void *src) {
    if (isEmpty(stack)) {
        fprintf(stderr, "%s", "Error, stack is empty\n");
        return;
    }
    //Point item = stack->array[stack->count - 1];
    memcpy(src, &((char *) stack->array)[(stack->count - 1) * stack->size], stack->size);
    //reset data of popped item
    memset(&((char *) stack->array)[(stack->count - 1) * stack->size], 0, stack->size);
    stack->count--;
    // shrink size of array if necessary
    if (stack->count > 0 && stack->count == stack->capacity / 4) {
        resize(stack->capacity / 2, stack);
    }

}

void *peek(const Stack *stack) {
    if (isEmpty(stack)) {
        fprintf(stderr, "%s", "Error, stack is empty\n");
        return NULL;
    }
    return &((char *) stack->array)[(stack->count - 1) * stack->size];
}

void iterator_fifo(const Stack *stack, void *buffer) {
    if (isEmpty(stack)) {
        fprintf(stderr, "%s", "Error, stack is empty\n");
    }
    memcpy(buffer, stack->array, stack->count * stack->size);
}




