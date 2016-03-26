#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

/* K&R C (Dennis M. Ritchie & Brian W. Kernighan)
 Exercise 1-8. Write a program to count blanks, tabs, and newlines.
*/

void hanger(void) {
	getchar();
}

int main(int argc, const char** argv) {

	atexit(hanger);

	if (argc != 2) {
		printf("Usage: app filepath.\n");
		return 1;
	}
	const char* filepath = argv[1];
	FILE* file = fopen(filepath, "r");
	if (!file) {
		printf("Unable to open \"%s\".\n", argv[1]);
		return 2;
	}

	int count = 0;

	char c = '\0';
	while ( (c = fgetc(file)) != EOF) {
		if (isspace(c)) ++count;
	}

	printf("Your file has a total of %d blank characters.\n", count);

	fclose(file);

	return 0;
}