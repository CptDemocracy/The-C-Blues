#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <errno.h>

/* K&R C (Dennis M. Ritchie & Brian W. Kernighan)
 Exercise 1-23. Write a program to remove all comments from a C program. Don't forget to
 handle quoted strings and character constants properly. C comments don't nest.
*/

int FileExists(const char* path) 
{
	if (!path) {
		return 0;
	}
	FILE* file = fopen(path, "r");
	if (!file) {
		return 0;
	}
	return 1;
}

int main(int argc, const char** argv) {

	if (argc < 3) {
		fprintf(stderr, "Usage: ./removeComments source destination.\n");
		return 1;
	}

	FILE* from = fopen(argv[1], "r");
	if (!from) {
		fprintf(stderr, "Error opening file \"%s\"", argv[1]);
		return 2;
	}

	if (FileExists(argv[2])) {
		fprintf(stderr, "Destination file with the same name already exists in the directory.\n");
		return 3;
	}

	FILE* to = fopen(argv[2], "w");
	if (!to) {
		fprintf(stderr, "Error creating a destination file.\n");
	}

	// parsing logic wip

	fclose(to);
	fclose(from);	

	return 0;
}
