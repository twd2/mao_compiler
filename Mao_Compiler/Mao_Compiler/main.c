#include "parser.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

	/*if (argc <= 1) {
		fprintf(stderr, "Argument error.\n");
		return 1;
	}*/

	_memory *mem = create_memory();

	if (!mem) {
		fprintf(stderr, "Bad alloc.\n");
		return 1;
	}

	/*char command[1005];
	FILE *file_input = fopen(argv[1], "r");
	if (!file_input) {
		fprintf(stderr, "Source file open error.\n");
		return 1;
	}
	while (!feof(file_input)) {
		fgets(command, 1005, file_input);
		pharser(mem, command);
	}
	fclose(file_input);*/
	
	parser(mem, "int a;");
	parser(mem, "a = 1 + 1;");
	parser(mem, "print(a);");

	return 0;
}
