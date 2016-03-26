#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <errno.h>

/* K&R C (Dennis M. Ritchie & Brian W. Kernighan)
 Exercise 1-14. Write a program to print a histogram of the frequencies 
 of different characters in its input.
*/

/*
 Originally, I intended to implement a lil' dynamic char-to-int dictionary, 
 (generic dictionary would probably be too bulky, if not an overkill for such a small 
 exercise). However, then I decided it would be unwieldy and impractical for this 
 problem. So I follow the KISS rule here.
*/

int main(int argc, const char** argv) {

	const size_t FREQS_LEN = UCHAR_MAX + 1;
	const char HIST_CHAR = '*';

	size_t freqs[UCHAR_MAX + 1] = { 0 }; // initialize to zeros
	size_t tableIndex = 0u;
	size_t maxWLen = 0u;

	char charBuffer[UCHAR_MAX + 1] = { 0 }; // initialize to zeros
	// will hold only the chars found in the input to avoid
	// traversing all UCHAR_MAX + 1 chars on each iteration,
	// when printing a histo
	size_t charBufferCount = 0u;

	char c = 0;

	while (1)
	{
		charBufferCount = 0u;
		memset(freqs, 0, (UCHAR_MAX + 1) * sizeof(size_t));
		memset(charBuffer, 0, (UCHAR_MAX + 1) * sizeof(char));

		printf(">>> ");

		while ( (c = getchar()) != '\n') {
			if (!isspace(c)) {
				tableIndex = (size_t)c;

				// rather than corrupt memory, fail
				if (tableIndex > FREQS_LEN) {
					fprintf(stderr, "Unsupported character type.\n");
					errno = ERANGE;
					return 1;
				}

				freqs[tableIndex] += 1u;

				if (freqs[tableIndex] > maxWLen) {
					maxWLen = freqs[tableIndex];
				}
			}
		}

		// find the used chars and copy them to the charBuffer
		for (size_t i = 0u; i < UCHAR_MAX + 1; ++i) {
			if (freqs[i] > 0u) {
				charBuffer[charBufferCount] = (char)i;
				++charBufferCount;
			}
		}

		while (maxWLen > 0u) {
			for (size_t i = 0u; i < charBufferCount; ++i) {
				c = charBuffer[i];
				tableIndex = (size_t)c;
				
				// no need to check for out of range here, since we 
				// checked that when we collected input, however, to 
				// avoid any unnecessary surprises, we double-check
				if (tableIndex > FREQS_LEN) {
					fprintf(stderr, "Unsupported character type.\n");
					errno = ERANGE;
					return 1;
				}

				if (freqs[tableIndex] == maxWLen) {
					freqs[tableIndex] = freqs[tableIndex] > 0u ? freqs[tableIndex] - 1 : 0u;
					putchar(HIST_CHAR);
				} else {
					putchar(' ');
				}
			}
			putchar('\n');
			--maxWLen;
		}

		for (size_t i = 0u; i < charBufferCount; ++i) {
			putchar(charBuffer[i]);
		}
		putchar('\n');
	}

	return 0;
}
