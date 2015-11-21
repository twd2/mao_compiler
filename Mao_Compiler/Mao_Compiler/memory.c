#include "memory.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Todo: try Hash to avoid visit through the linked list

//_memory *p_head = NULL;

unsigned int error = NO_ERROR;

_memory *create_memory() {
	_memory *p_node = (_memory *)malloc(sizeof(_memory));

	if (p_node) {
		p_node->variable.int_value = 0;
		p_node->variable.type = INT;
		strcpy(p_node->name, "@");
		p_node->p_next = NULL;
		return p_node;
	}
	else {
		error = MALLOC_ERROR;
	}
	return NULL;
}

void add_node(_memory *p_head, _memory *_p_node) {
	_memory *p_current = p_head;

	if (!p_head) {
		// If p_head is NULL
		p_head = _p_node;
		_p_node->p_next = NULL;
	}
	else {
		// else, find the last node
		while (p_current->p_next) {
			p_current = p_current->p_next;
		}
		p_current->p_next = _p_node;
		_p_node->p_next = NULL;
	}
	return;
}

void add_int_variable(_memory *p_head, _name_string _name, int _value) {
	_memory *p_node = (_memory *)malloc(sizeof(_memory));

	if (p_node) {
		p_node->variable.int_value = _value;
		p_node->variable.type = INT;
		strcpy(p_node->name, _name);

		add_node(p_head, p_node);
	}
	else {
		error = MALLOC_ERROR;
	}

	return;
}

void add_double_variable(_memory *p_head, _name_string _name, double _value) {
	_memory *p_node = (_memory *)malloc(sizeof(_memory));

	if (p_node) {
		p_node->variable.double_value = _value;
		p_node->variable.type = DOUBLE;
		strcpy(p_node->name, _name);

		add_node(p_head, p_node);
	}
	else {
		error = MALLOC_ERROR;
	}

	return;
}

_variable get_variable_by_name(_memory *p_head, _name_string _name) {
	_memory *p_current = p_head;
	_variable var_null = {INT, 0, 0};
	if (!p_current) {
		error = MEMORY_EMPTY;
		return var_null;
	}
	else {
		while (p_current) {
			if (!strcmp(p_current->name, _name)) {
				return p_current->variable;
			}
			p_current = p_current->p_next;
		}
	}
	error = MATCH_ERROR;
	return var_null;
}

_type get_type_by_name(_memory *p_head, _name_string _name) {
	return get_variable_by_name(p_head, _name).type;
}

int get_int_value_by_name(_memory *p_head, _name_string _name) {
	return get_variable_by_name(p_head, _name).int_value;
}

double get_double_value_by_name(_memory *p_head, _name_string _name) {
	return get_variable_by_name(p_head, _name).double_value;
}

void assign_variable(_variable *_destination, const _variable *_source) {
	_destination->type = _source->type;
	switch (_destination->type) {
	case INT:
		_destination->int_value = _source->int_value;
		break;
	case DOUBLE:
		_destination->double_value = _source->double_value;
		break;
	}
	return;
}
