#pragma once

#ifndef UTILITY_H
#define UTILITY_H

#include "vector.h"
#include <stdbool.h>

// Function to append a string to a string
void string_append(char *_des, const char *_src);

// Function to replace a character of a string
void string_replace(char *_des, const char _ch, const unsigned int _pos);

// Function to instert a string to a string
void string_insert(char *_des, const char *_src, const unsigned int _pos);

// Function to get a sub-string of a string
void string_sub(char *_des, const char *_src, const unsigned int _pos, const unsigned int _len);

// Function to split a string, returning the count of sub-strings
int string_split(_vector *vec, const char *src, const char delim);

// Function to purify a string, preserving only characters and numbers
char *string_purify(const char *str);

// Function to delete all spaces in a string
void string_clearspace(char *str);

// Function to check whether a string starts with a specific string ignoring leading spaces
int string_startswith(char *str, const char *start);

#endif
