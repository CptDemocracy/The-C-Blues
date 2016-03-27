#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <errno.h>

/* K&R C (Dennis M. Ritchie & Brian W. Kernighan)
 Exercise 1-19. Write a function reverse(s) that reverses the character string s. Use it to
 write a program that reverses its input a line at a time.
*/

#define BUFFER_INIT_CAPACITY 128

char* ReverseStringInPlace(char* str, size_t len) {
	// len can never be negative since it's unsigned
	// but to play it safe - in case someone changes
	// unsigned to signed for the len variable - we
	// prefer to provide for that to avoid surprises
	if (!str || len <= 0) {
		errno = EINVAL;
		return NULL;
	}
	char temp = 0;
	for (size_t i = 0, j = len - 1; i < j; ++i, --j) {
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
	}
	return str;
}

int main(int argc, const char** argv) {

	size_t bufferCapacity = BUFFER_INIT_CAPACITY;
	char* buffer = (char*)malloc(sizeof(char) * BUFFER_INIT_CAPACITY);
	if (!buffer) {
		errno = ENOMEM;
		return 1;
	}

	size_t bufferCount = 0;

	char c = 0;

	while (1)
	{
		bufferCount = 0;

		printf(">>> ");

		while ( (c = getchar()) != '\n') {		
					
			if (bufferCount >= bufferCapacity - 1) 
			{
				// a safeguard in case someone accidentally changes bufferCapacity to 0
				bufferCapacity = (bufferCapacity > 0) ? bufferCapacity * 2 : BUFFER_INIT_CAPACITY;
				buffer = (char*)realloc(buffer, bufferCapacity);
				if (!buffer) {
					errno = ENOMEM;
					return 1;
				}
			}
			buffer[bufferCount] = c;
			++bufferCount;
						
		}
		buffer[bufferCount] = 0;

		ReverseStringInPlace(buffer, strlen(buffer));

		printf("%s\n", buffer);
	}

	free(buffer);
	buffer = NULL;

	return 0;
}