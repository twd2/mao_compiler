#include "memory.h"
#include "utility.h"
#include "expression.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
	char as[200] = "a/b + pl+(4*m*g)/(pi*d*d)";
	_variable res;

	_memory *mem = create_memory();

	if (!mem)
	{
		fprintf(stderr, "Bad alloc.\n");
		return 1;
	}

	add_int_variable(mem, "a", 1);
	add_int_variable(mem, "b", 0);
	add_double_variable(mem, "pl", 101.25);
	add_double_variable(mem, "m", 11.18);
	add_double_variable(mem, "g", 9.794);
	add_double_variable(mem, "pi", 3.1415927);
	add_double_variable(mem, "d", 13.981);

	pharse(as);
	fprintf(stderr, "%s\n", as);
	convert(as);
	fprintf(stderr, "%s\n", as);
	res = calculate(mem, as);

	if (res.type == ERRORVALUE) {
		fprintf(stderr, "error: %d\n", res.int_value);
	}
	else {
		fprintf(stderr, "%lf\n", res.double_value);
	}

	return 0;
}
