#include "stack.h"
#include <stdlib.h>

_stack *stack_new(size_t cap) {
	if (cap <= 0) {
		return NULL;
	}
	_stack *stack = (_stack *)malloc(sizeof(_stack));
	stack->capacity = cap;
	stack->size = 0;
	stack->data = (void **)malloc(stack->capacity * sizeof(void *));
	return stack;
}

size_t stack_size(_stack *stack) {
	return stack->size;
}

void **stack_top(_stack *stack) {
	return stack->data[stack->size - 1];
}

void stack_pop(_stack *stack) {
	if (stack_size(stack) <= 0) {
		return;
	}
	free(stack->data[stack->size - 1]);
	stack->data[stack->size - 1] = NULL;
	--stack->size;
	return;
}

void stack_push(_stack *stack, void *_data) {
	if (stack->size == stack->capacity) {
		stack->capacity *= 2;
		stack->data = (void **) realloc(stack->data, stack->capacity * sizeof(void *));
	}
	stack->data[stack->size] = _data;
	++stack->size;
	return;
}

void stack_push_constant(_stack *stack, int var) {
	int *p_var = (int *)malloc(sizeof(int));
	*p_var = var;
	stack_push(stack, p_var);
	return ;
}