#pragma once

#ifndef _MEMORY_H
#define _MEMORY_H

#include "map.h"
#include <stdbool.h>

#define NO_ERROR			0x00
#define MATCH_ERROR			0x01
#define MALLOC_ERROR		0x02
#define MEMORY_EMPTY		0x03
#define LOGIC_ERROR			0x04
#define DIVIDED_BY_ZERO		0x05
#define USED_BEFORE_DEFINE	0x06
#define VAR_REDEFINE		0x07

typedef enum { INT, DOUBLE, ERRORVALUE } _type;

typedef struct _variable {
	_type type;
	bool is_constant;
	int int_value;
	double double_value;
	char name[1]; // variable length name
} _variable;

// Function to add a int variable
void add_int_variable(_map *mem, char *_name, int _value);

// Function to add a double variable
void add_double_variable(_map *mem, char *_name, double _value);

// Function to change the value of a variable
void set_variable(_map *mem, char *_name, _variable _var);

// Function to get a variable given by name
_variable *get_variable_by_name(_map *mem, char *_name);

// Function to print a variable
void print_variable(_variable *var);

// Function to find type by specific name
_type get_type_by_name(_map *mem, char *_name);

// Function to get int value by specific name
int get_int_value_by_name(_map *mem, char *_name);

// Function to get double value by specific name
double get_double_value_by_name(_map *mem, char *_name);

// Function for variable assignment
void assign_variable(_variable *_destination, const _variable *_source);

#endif
