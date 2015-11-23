#include "vector.h"
#include "pharser.h"
#include "utility.h"
#include "memory.h"
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
	char temp_identity[10], temp_varnames[1005];
	const char double_declare[] = "double ";
	const char int_declare[] = "int ";
	const int double_declare_len = strlen(double_declare);
	const int int_declare_len = strlen(int_declare);

	string_sub(temp_identity, statement, 0, double_declare_len);
	if (!strcmp(temp_identity, double_declare)) {
		// variable declared as a double
		int i;
		for (i = double_declare_len - 1; i < strlen(statement); ++i) {
			if (statement[i] != ' ') {
				break;
			}
		}
		string_sub(temp_varnames, statement, i, len);
		_vector *vec = vector_new(1);
		int count = string_split(vec, temp_varnames, ',');
		for (i = 0; i < count; ++i) {
			char *name_purified = string_purify((char *)(*vector_get(vec, i)), 0);
			add_double_variable(mem, name_purified, 0);
			free(name_purified);
		}
		vector_deepfree(vec);
	}
	else if (!strcmp(temp_identity, int_declare)) {
		// variable declared as a int
		int i;
		for (i = int_declare_len - 1; i < strlen(statement); ++i) {
			if (statement[i] != ' ') {
				break;
			}
		}
		string_sub(temp_varnames, statement, i, len);
		_vector *vec = vector_new(1);
		int count = string_split(vec, temp_varnames, ',');
		for (i = 0; i < count; ++i) {
			char *name_purified = string_purify((char *)(*vector_get(vec, i)), 0);
			add_int_variable(mem, name_purified, 0);
			free(name_purified);
		}
	}
	return;
}
