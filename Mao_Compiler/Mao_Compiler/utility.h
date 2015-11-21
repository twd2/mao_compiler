#pragma once

#ifndef UTILITY_H
#define UTILITY_H

// Function to append a string to a string
extern void string_append(char* _destination, const char* _source);

// Function to instert a string to a string
extern void string_insert(char* _destination, const char* _source, const unsigned int _position);

// Function to get a sub-string of a string
extern void string_sub(char* _destination, const char* _source, const unsigned int _position, const unsigned int _length);

#endif
