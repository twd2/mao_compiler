#include "pharser.h"
#include "utility.h"
#include <string.h>

void pharser(const char *statement) {
	/*
	 * there're three occasions:
	 * (1) variable declaration
	 * (2) variable printing
	 * (3) variable assignment
	 */

	// variable declaration
	char temp[10];
	string_sub(temp, statement, 0, strlen("double "));
	if (!strcmp(temp, "double ")) {
		// variable declared as a double

	}
	return;
}
