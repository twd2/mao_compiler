#include "parser.h"
#include "utility.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main(int argc, char *argv[]) {

	_memory *mem = create_memory();

	if (!mem) {
		fprintf(stderr, "Bad alloc\n");
		return 1;
	}

	char command[1005];
	FILE *file_input = NULL;
	if (argc > 1) {
		file_input = fopen(argv[1], "r");
	}
	else {
		file_input = stdin;
	}

	if (!file_input) {
		fprintf(stderr, "Source file open error\n");
		return 1;
	}

	while (true) {
		fgets(command, 1005, file_input);
		if (feof(file_input)) {
			break;
		}
		command[strlen(command) - 1] = '\0'; //remove last '\n'
		parser(mem, command);
	}
	fclose(file_input);
	
	/* test for memory leaking:

	 parser(mem, "int a;");
	 while (1) {
		parser(mem, "a = -1;");
		parser(mem, "a = 1/0;");
	 }

	 */

	return 0;
}
