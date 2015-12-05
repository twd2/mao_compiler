#include "parser.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

	_memory *mem = create_memory();

	if (!mem) {
		fprintf(stderr, "Bad alloc.\n");
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
		fprintf(stderr, "Source file open error.\n");
		return 1;
	}

	//while (!feof(file_input)) {
	//	fgets(command, 1005, file_input);
	//	command[strlen(command) - 1] = '\0'; //remove last '\n'
	//	parser(mem, command);
	//}
	//fclose(file_input);
	
	parser(mem, "int a;");
	while (1) {
		parser(mem, "a = -1;");
		parser(mem, "a = a + 1;");
	}

	return 0;
}
