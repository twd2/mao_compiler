#pragma once

#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>

typedef struct _vector {
	void **data;
	size_t capacity;
	size_t size;
} _vector;

// Function to create a new vector
_vector *vector_new(size_t cap);

// Function to add a data to vector
void vector_add(_vector *vec, void *_data);

// Function to get the pointer of the value indexed i from the vector
void **vector_get(_vector *vec, size_t i);

// Function to get the size of vector
size_t vector_size(_vector *vec);

// Function to get the capacity of vector
size_t vector_capacity(_vector *vec);

// Function to get the beginning data of vector
void **vector_begin(_vector *vec);

// Function to get the ending data of vector
void **vector_end(_vector *vec);

// Function to detele the vector preserving the values
void vector_free(_vector *vec);

// Function to delete the vector and its values
void vector_deepfree(_vector *vec);

#endif
