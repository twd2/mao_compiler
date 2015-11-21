#include "memory.h"
#include "utility.h"
#include "expression.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
	char as[200] = "pl+(4*m*g)/(pi*d*d)";
	double res;

	add_double_variable("pl", 101.25);
	add_double_variable("m", 11.18);
	add_double_variable("g", 9.794);
	add_double_variable("pi", 3.1415927);
	add_double_variable("d", 13.981);

	pharse(as);
	fprintf(stderr, "%s\n", as);
	convert(as);
	fprintf(stderr, "%s\n", as);
	res = calculate(as);
	fprintf(stderr, "%lf\n", res);
	return 0;
}
