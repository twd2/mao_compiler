#include "memory.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int error = NO_ERROR;

void add_int_variable(_map *mem, char *_name, int _value) {
	//                                                       variable length name
	_variable *var = (_variable *)malloc(sizeof(_variable) + (strlen(_name) + 1));
	if (var) {
		var->int_value = _value;
		var->type = INT;
		var->is_constant = false;
		strcpy(var->name, _name);
		void **old_var_ptr;
		_variable *old_var;
		if ((old_var_ptr = map_get(mem, _name)) && (old_var = (_variable *)*old_var_ptr)) {
			free(var);
			error = VAR_REDEFINE;
			return;
		}
		map_add(mem, _name, var);
	}
	else {
		error = MALLOC_ERROR;
	}

	return;
}

void add_double_variable(_map *mem, char *_name, double _value) {
	//                                                       variable length name
	_variable *var = (_variable *)malloc(sizeof(_variable) + (strlen(_name) + 1));
	if (var) {
		var->double_value = _value;
		var->type = DOUBLE;
		var->is_constant = false;
		strcpy(var->name, _name);
		void **old_var_ptr;
		_variable *old_var;
		if ((old_var_ptr = map_get(mem, _name)) && (old_var = (_variable *)*old_var_ptr)) {
			free(var);
			error = VAR_REDEFINE;
			return;
		}
		map_add(mem, _name, var);
	}
	else {
		error = MALLOC_ERROR;
	}

	return;
}

void set_variable(_map *mem, char *_name, _variable _var) {
	_variable *des = get_variable_by_name(mem, _name);
	// bug fixed: assignment a double to a int, caused data lost
	if (des->type == INT && _var.type == DOUBLE) {
		// des->type won't change
		des->int_value = (int)_var.double_value;
	}
	else if (des->type == DOUBLE && _var.type == INT) {
		des->double_value = (double)_var.int_value;
	}
	else {
		des->type = _var.type;
		des->int_value = _var.int_value;
		des->double_value = _var.double_value;
	}
	return;
}

_variable *get_variable_by_name(_map *mem, char *_name) {
	void **var_ptr;
	var_ptr = map_get(mem, _name);
	if (var_ptr) {
		return (_variable *)*var_ptr;
	}
	else {
		return NULL;
	}
}

void print_variable(_variable *var) {
	switch (var->type)
	{
	case INT:
		printf("%d\n", var->int_value);
		break;
	case DOUBLE:
		printf("%lf\n", var->double_value);
		break;
	case ERRORVALUE:
		break;
	}
	return;
}

_type get_type_by_name(_map *mem, char *_name) {
	return (*get_variable_by_name(mem, _name)).type;
}

int get_int_value_by_name(_map *mem, char *_name) {
	return (*get_variable_by_name(mem, _name)).int_value;
}

double get_double_value_by_name(_map *mem, char *_name) {
	return (*get_variable_by_name(mem, _name)).double_value;
}

void assign_variable(_variable *_destination, const _variable *_source) {
	_destination->type = _source->type;
	switch (_destination->type) {
	case INT:
	case ERRORVALUE:
		_destination->int_value = _source->int_value;
		break;
	case DOUBLE:
		_destination->double_value = _source->double_value;
		break;
	}
	return;
}
