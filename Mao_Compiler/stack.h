#pragma once

#ifndef STACK_STACK_H
#define STACK_STACK_H

#include <stddef.h>

typedef struct _stack {
	void **data;
	size_t capacity;
	size_t size;
} _stack;

// Function to create a new stack
_stack *stack_new(size_t cap);

// Function to get the size of the stack
size_t stack_size(_stack *stack);

// Function to get the top of the stack
void **stack_top(_stack *stack);

// Function to remove the top element of the stack and the value
void stack_pop_and_free(_stack *stack);

// Function to remove the top element of the stack
void stack_pop(_stack *stack);

// Function to push a new element to the top of the stack
void stack_push(_stack *stack, void *data);

// Function to push a new element copied from stack memory to heap memory to the top stack
void stack_copy_and_push(_stack *stack, void *data, size_t size);

// Function to push a string to the top of the stack
void stack_push_string(_stack *stack, const char *str);

// Function to free a stack and its values
void stack_deepfree(_stack *stack);

// Function to deep free a stack
void stack_free(_stack *stack);

#endif //STACK_STACK_H
