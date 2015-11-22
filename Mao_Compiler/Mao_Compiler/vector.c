#include "vector.h"
#include <stddef.h>
#include <stdlib.h>

_vector *vector_new(size_t cap) {
	if (cap <= 0) {
		return NULL;
	}
	_vector *vec = (_vector *)malloc(sizeof(_vector));
	vec->capacity = cap;
	vec->size = 0;
	vec->data = (void **)malloc(vec->capacity * sizeof(void *));
	return vec;
}

void vector_add(_vector *vec, void *_data) {
	if (vec->size == vec->capacity) {
		vec->capacity *= 2;
		vec->data = (void **)realloc(vec->data, vec->capacity * sizeof(void *));
	}
	vec->data[vec->size] = _data;
	++vec->size;
	return;
}

void **vector_get(_vector *vec, size_t i) {
	return vec->data + i;
}

size_t vector_size(_vector *vec) {
	return vec->size;
}

size_t vector_capacity(_vector *vec) {
	return vec->capacity;
}

void **vector_begin(_vector *vec) {
	return vec->data;
}

void **vector_end(_vector *vec) {
	return vec->data + vec->size;
}

void vector_free(_vector *vec) {
	free(vec->data);
	vec->data = NULL;
	free(vec);
	vec = NULL;
	return;
}

void vector_deepfree(_vector *vec) {
	for (size_t i = 0; i < vec->size; ++i) {
		free(vec->data[i]);
		vec->data[i] = NULL;
	}
	free(vec->data);
	vec->data = NULL;
	free(vec);
	vec = NULL;
}
