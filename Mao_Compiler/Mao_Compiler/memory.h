#pragma once

#ifndef _MEMORY_H
#define _MEMORY_H

#define NO_ERROR        0x00
#define MATCH_ERROR     0x01
#define MALLOC_ERROR    0x02
#define MEMORY_EMPTY    0x03
#define LOGIC_ERROR     0x04
#define DIVIDED_BY_ZERO 0x05

typedef enum { INT, DOUBLE } _type;
typedef char _name_string[25];

typedef struct _variable {
	_type type;
	int int_value;
	double double_value;
} _variable;

typedef struct _memory {
	_name_string name;
	_variable variable;
	struct _memory *p_next;
} _memory;

// Funtion to get error information
int get_last_error(void);

// Funtion to add a int variable
extern void add_int_variable(_name_string _name, int _value);

// Funtion to add a double variable
extern void add_double_variable(_name_string _name, double _value);

// Function to add a new node
extern void add_node(_memory *_p_node);

// Function to get a variable given by name
extern _variable get_variable_by_name(_name_string _name);

// Function to find type by specific name
extern _type get_type_by_name(_name_string _name);

// Function to get int value by specific name
extern int get_int_value_by_name(_name_string _name);

// Function to get double value by specific name
extern double get_double_value_by_name(_name_string _name);

// Function for variable assignment
extern void assign_variable(_variable *_destination, const _variable *_source);

#endif
