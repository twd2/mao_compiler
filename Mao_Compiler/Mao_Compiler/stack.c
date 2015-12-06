#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
	return stack->data + stack->size - 1;
}

void stack_pop_and_free(_stack *stack) {
	if (stack->size <= 0) {
		return;
	}
	free(stack->data[stack->size - 1]);
	stack->data[stack->size - 1] = NULL;
	--stack->size;
	return;
}

void stack_pop(_stack *stack) {
	if (stack_size(stack) <= 0) {
		return;
	}
	--stack->size;
	return;
}

void stack_push(_stack *stack, void *data) {
	if (stack->size == stack->capacity) {
		stack->capacity *= 2;
		stack->data = (void **) realloc(stack->data, stack->capacity * sizeof(void *));
	}

	stack->data[stack->size] = data;
	++stack->size;
	return;
}

void stack_copy_and_push(_stack *stack, void *data, size_t size) {
	if (stack->size == stack->capacity) {
		stack->capacity *= 2;
		stack->data = (void **)realloc(stack->data, stack->capacity * sizeof(void *));
	}

	void *p_data_copied = malloc(size);
	memcpy(p_data_copied, data, size);
	stack->data[stack->size] = p_data_copied;
	++stack->size;
	return;
}

void stack_deepfree(_stack *stack) {
	while (stack_size(stack) > 0) {
		stack_pop_and_free(stack);
	}
	free(stack->data);
	stack->data = NULL;
	free(stack);
	stack = NULL;
	return;
}

void stack_free(_stack *stack) {
	free(stack->data);
	stack->data = NULL;
	free(stack);
	stack = NULL;
	return;
}

void stack_push_string(_stack *stack, const char *str) {
	char *p_str = (char *)malloc(sizeof(char) * (strlen(str) + 1));
	strcpy(p_str, str);
	stack_push(stack, p_str);
	return;
}
