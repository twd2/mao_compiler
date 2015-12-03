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

// Function to remove the top element of the stack
void stack_pop(_stack *stack);

// Function to push a new element to the top of the stack
void stack_push(_stack *stack, void *_data);

// Function to push a new constant to the top of the stack
void stack_push_constant(_stack *stack, int var);

#endif //STACK_STACK_H
