#include "memory.h"
//#include "expression.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
	char as[200] = "i123*2+1*61";
	double res;

	add_int_variable("i123", 1);
	add_double_variable("ddd", 1.1);

	pharse(as);
	fprintf(stderr, "%s\n", as);
	convert(as);
	fprintf(stderr, "%s\n", as);
	res = calculate(as);
	fprintf(stderr, "%lf\n", res);
	return 0;
}
