#include "vector.h"
#include "pharser.h"
#include "utility.h"
#include "memory.h"
#include "expression.h"
#include <stdio.h>
#include <string.h>

void pharser(_memory *mem, const char *statement) {
	/*
	 * there're three occasions:
	 * (1) variable declaration
	 * (2) variable printing
	 * (3) variable assignment
	 */

	int len = strlen(statement);

	// variable declaration
	char temp_str[1005];
	const char double_declare[] = "double ";
	const char int_declare[] = "int ";
	const char print_stat[] = "print";
	const int double_declare_len = strlen(double_declare);
	const int int_declare_len = strlen(int_declare);

	if (string_startswith(statement, double_declare)) {
		// variable declared as a double
		int i;
		for (i = double_declare_len - 1; i < len; ++i) {
			if (statement[i] != ' ') {
				break;
			}
		}
		string_sub(temp_str, statement, i, len);
		_vector *vec = vector_new(1);
		int count = string_split(vec, temp_str, ',');
		for (i = 0; i < count; ++i) {
			char *name_purified = string_purify((char *)(*vector_get(vec, i)));
			add_double_variable(mem, name_purified, 0);
			free(name_purified);
		}
		vector_deepfree(vec);
	}
	
	if (string_startswith(statement, int_declare)) {
		// variable declared as a int
		int i;
		for (i = int_declare_len - 1; i < len; ++i) {
			if (statement[i] != ' ') {
				break;
			}
		}
		string_sub(temp_str, statement, i, len);
		_vector *vec = vector_new(1);
		int count = string_split(vec, temp_str, ',');
		for (i = 0; i < count; ++i) {
			char *name_purified = string_purify((char *)(*vector_get(vec, i)));
			add_int_variable(mem, name_purified, 0);
			free(name_purified);
		}
	}

	// variable printing
	const char print_declare1[] = "print ";
	const char print_declare2[] = "print(";
	const int print_declare_len = strlen(print_declare1);

	if (string_startswith(statement, print_declare1) ||
		string_startswith(statement, print_declare2)) {
		// print statement
		int i;
		for (i = print_declare_len - 1; i < len; ++i) {
			if (statement[i] == ')') {
				break;
			}
		}
		string_sub(temp_str, statement, print_declare_len, i - print_declare_len);
		pharse(temp_str);
		convert(temp_str);
		_variable var = calculate(mem, temp_str);
		print_variable(var);
	}

	// variable assignment
	if (strchr(statement, '=')) {
		_vector *vec = vector_new(1);
		int count = string_split(vec, statement, '=');
		char *temp_statement = (char *)(*vector_get(vec, count - 1));
		pharse(temp_statement);
		convert(temp_statement);
		_variable var = calculate(mem, temp_statement);
		for (int i = 0; i < count - 1; ++i) {
			char *purified = string_purify((char *)(*vector_get(vec, i)));
			set_variable(mem, purified, var);
		}
	}
	return;
}
