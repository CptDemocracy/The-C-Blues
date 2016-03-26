#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

/* K&R C (Dennis M. Ritchie & Brian W. Kernighan)
 Exercise 1-10. Write a program to copy its input to its output, 
 replacing each tab by \t, each backspace by \b, and each backslash by \\. 
 This makes tabs and backspaces visible in an unambiguous way.
*/

int main(int argc, const char** argv) {

	char c;

	while (1)
	{
		printf(">>> ");

		while ( (c = getchar()) != '\n') {
			switch (c) {
				case '\t':
					printf("\\t");
					break;
				case '\b':
					printf("\\b");
					break;
				case '\\':
					printf("\\\\");
					break;
				default:
					putchar(c);
					break;
			}
		}
		putchar('\n');

	}

	return 0;
}