#include <string.h>
#include <stdio.h>

/* K&R C (Dennis M. Ritchie & Brian W. Kernighan)
 Exercise 4-7. Write a routine ungets(s) that will push back an entire string onto the input.
*/

#define BUFFER_SIZE	256

const char* ungets(const char* s, FILE* stream) {
	if (!s) return NULL;
	for (size_t i = strlen(s); i > 0; --i) {
		ungetc(s[i - 1], stream);
	}	
	return s;
}

int main(void) {

	char buffer[BUFFER_SIZE] = { 0 };

	char c = 0;
	char d = 0;

	while (1)
	{
		fgets(buffer, BUFFER_SIZE, stdin);
		printf("%s\n", buffer);
		ungets(buffer, stdin);
	}

    getchar();
    return 0;
}
