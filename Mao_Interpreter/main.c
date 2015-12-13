#include "parser.h"
#include "utility.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main(int argc, char *argv[]) {

	_map *mem = map_new_node();

	if (!mem) {
		fprintf(stderr, "Bad alloc\n");
		return 1;
	}

	char command[1005]; // enough?
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
	
	//test for memory leaking:

	//char stat[10000] = "";

	//while (1) {
	//	map_deepfree(mem);
	//	mem = map_new_node();

	//	for (int i = 0; i < 100000; ++i) {
	//		sprintf(stat, "int a%d;", i);
	//		parser(mem, stat);
	//	}
	//	parser(mem, "int a;");
	//	parser(mem, "double b;");

	//	parser(mem, "a = -1;");
	//	parser(mem, "b = +1.0;");

	//	parser(mem, "print(a0);");
	//	//parser(mem, "a = 1/0;");
	//}
	
	map_deepfree(mem);
	mem = NULL;

	return 0;
}
