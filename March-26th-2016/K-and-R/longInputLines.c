#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <errno.h>

/* K&R C (Dennis M. Ritchie & Brian W. Kernighan)
 Exercise 1-17. Write a program to print all input lines that are longer than 80 characters.
*/

#define TARGET_INPUT_LENGTH_CSTR	"80"
#define TARGET_INPUT_LENGTH			80
#define BUFFER_INIT_CAPACITY		128

int main(int argc, const char** argv) {
	
	const char* INPUT_TOO_SHORT_MSG = "Your input was shorter than " TARGET_INPUT_LENGTH_CSTR " characters.";

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
		memset(buffer, 0, sizeof(char) * bufferCapacity);

		printf(">>> ");

		while ( (c = getchar()) && c != '\n') {
			if (bufferCount >= bufferCapacity - 1) {

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
		// don't really have to do it, since we always keep an extra
		// byte for the null terminating character and reset all bytes
		// to zeros at each iteration, however, we choose to play it
		// safe
		buffer[bufferCount] = 0;

		size_t inputLen = strlen(buffer);

		if (inputLen < TARGET_INPUT_LENGTH) {
			printf("%s\n", INPUT_TOO_SHORT_MSG);
		}
		else {
			printf("%s\n", buffer); 
		}		
	}

	return 0;
}
