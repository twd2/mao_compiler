#pragma once

#ifndef UTILITY_H
#define UTILITY_H

#include "vector.h"

// Function to append a string to a string
void string_append(char* _des, const char* _src);

// Function to instert a string to a string
void string_insert(char* _des, const char* _src, const unsigned int _pos);

// Function to get a sub-string of a string
void string_sub(char* _des, const char* _src, const unsigned int _pos, const unsigned int _len);

// Function to split a string, returning the count of sub-strings
int string_split(_vector *vec, const char *src, const char delim);

// Function to purify a string, preserving only characters and numbers
char *string_purify(const char *str);

int string_startswith(char* _str, const char* _x);

#endif
