//
// Created by vadim on 07.10.2019.
//

#ifndef PARK_SEM1_C_DZ1_STACK_H
#define PARK_SEM1_C_DZ1_STACK_H

#include "main.h"
#include <stdlib.h>
#include <stdbool.h>

// A structure to represent a stack
struct Stack;

typedef struct Stack Stack;

// create empty stack, size param is size of 1 element in stack
Stack *create_stack(size_t size);

//free memory connected with stack
void delete_stack(Stack *stack);

// Check if stack is empty
bool isEmpty(const Stack *stack);

// Returns the number of items in the stack.
int stack_size(const Stack *stack);

// Function to add an item to stack.
void push(Stack *stack, void *item);

// Function to remove an item from stack
void pop(Stack *stack, void *src);

// Function to check top item from stack
//returns NULL if stack is empty
void *peek(const Stack *stack);


//returns iterator fifo order to user allocated buffer
//warning: doesnt check buffer size!
void iterator_fifo(const Stack *stack, void *buffer);

#endif //PARK_SEM1_C_DZ1_STACK_H
