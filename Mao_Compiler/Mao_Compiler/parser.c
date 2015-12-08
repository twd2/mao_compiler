#include "vector.h"
#include "parser.h"
#include "memory.h"
#include "utility.h"
#include "expression.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void parser(_memory *mem, const char *statement) {
	/*
	 * there're three occasions:
	 * (1) variable declaration
	 * (2) variable printing
	 * (3) variable assignment
	 */

	_vector *vec_statement = vector_new(1);
	int count = string_split(vec_statement, statement, ';');

	char *current_statement = (char *)malloc(sizeof(char));

	for (int i = 0; i < count; ++i) {

		size_t len = strlen((char *)*vector_get(vec_statement, i));
		current_statement = (char *)realloc(current_statement, sizeof(char) * (len + 1));
		strcpy(current_statement, (char *)*vector_get(vec_statement, i));

		if (!strcmp(current_statement, "")) {
			break;
		}

		bool is_assignment = true;

		// variable declaration
		char temp_str[1005]; // TODO(twd2): enough?
		const char double_declare[] = "double ";
		const char int_declare[] = "int ";
		const size_t double_declare_len = strlen(double_declare);
		const size_t int_declare_len = strlen(int_declare);

		int str_int_start_pos = string_startswith(current_statement, int_declare);
		int str_double_start_pos = string_startswith(current_statement, double_declare);

		if (str_double_start_pos != -1) {
			// variable declared as a double
			is_assignment = false;

			size_t j;
			for (j = str_double_start_pos + double_declare_len; j < len; ++j) {
				if (current_statement[j] != ' ') {
					break;
				}
			}
			string_sub(temp_str, current_statement, j, len);
			_vector *vec_declare = vector_new(1);
			int count = string_split(vec_declare, temp_str, ',');
			for (j = 0; j < count; ++j) {
				char *name_purified = string_purify((char *)(*vector_get(vec_declare, j)));
				add_double_variable(mem, name_purified, 0);
				free(name_purified);
			}
			vector_deepfree(vec_declare);
		}

		if (str_int_start_pos != -1) {
			// variable declared as a int
			is_assignment = false;

			size_t j;
			for (j = str_int_start_pos + int_declare_len; j < len; ++j) {
				if (current_statement[j] != ' ') {
					break;
				}
			}
			string_sub(temp_str, current_statement, j, len);
			_vector *vec_declare = vector_new(1);
			int count = string_split(vec_declare, temp_str, ',');
			for (j = 0; j < count; ++j) {
				char *name_purified = string_purify((char *)(*vector_get(vec_declare, j)));
				add_int_variable(mem, name_purified, 0);
				free(name_purified);
			}
		}

		// variable printing
		const char print_declare1[] = "print ";
		const char print_declare2[] = "print(";
		const size_t print_declare_len = strlen(print_declare1);

		if (string_startswith(current_statement, print_declare1) != -1 ||
			string_startswith(current_statement, print_declare2) != -1) {
			// print statement
			is_assignment = false;

			int j;
			for (j = print_declare_len - 1; j < len; ++j) {
				if (current_statement[j] == ')') {
					break;
				}
			}
			string_sub(temp_str, current_statement, print_declare_len, j - print_declare_len);
			parse(temp_str);
			convert(temp_str);
			_variable var = calculate(mem, temp_str);
			if (var.type == ERRORVALUE) {
				catch_error(var.int_value);
				break;
			}
			print_variable(var);
		}

		// variable assignment
		if (is_assignment) {
			strcpy(temp_str, current_statement);
			string_clearspace(temp_str);
			parse(temp_str);
			convert(temp_str);
			_variable var = calculate(mem, temp_str);
			if (var.type == ERRORVALUE) {
				catch_error(var.int_value);
				break;
			}
		}

	}

	free(current_statement);
	vector_deepfree(vec_statement);
	return;
}

void catch_error(int error_code) {
	switch (error_code) {
	case DIVIDED_BY_ZERO:
		printf("divided by ZERO\n");
		break;
	case USED_BEFORE_DEFINE:
		printf("Using undefined variable\n");
		break;
	default:
		printf("Unknown error\n");
		break;
	}
}
