#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <ctype.h>

/* K&R C (Dennis M. Ritchie & Brian W. Kernighan)
 Exercise 3-3. Write a function expand(s1,s2) that expands shorthand notations like a-z in
 the string s1 into the equivalent complete list abc...xyz in s2. Allow for letters of either case
 and digits, and be prepared to handle cases like a-b-c and a-z0-9 and -a-z. Arrange that a
 leading or trailing - is taken literally.
*/

#define BUFFER_SIZE 64

void Expand(char* buffer, size_t bufferLen, const char* str);

void ExpandHelper(char* buffer, size_t bufferLen, const char* str);

int main(void) {

	char buffer[BUFFER_SIZE] = { 0 };
	
    // const char* str = "--a-c-e0-9A-C-E-";
    
	// const char* str = "a-b-c";
	
	// const char* str = "---a-zA-Z---";

	const char* str = "a-z0-9";

	Expand(buffer, BUFFER_SIZE, str);
    printf("%s.\n", buffer);

	getchar();

	return 0;
}

void Expand(char* buffer, size_t bufferLen, const char* str) {
	
	if (!buffer || bufferLen == 0 || !str) {
		errno = EINVAL;
		return;
	}

	static const SEPARATOR = '-';
	
	size_t i = 0;
	const char* pchar = &str[0];

	// skip whitespace at the beginning of the string
	while (isblank(*pchar)) ++pchar;

	// add leading dashes
	while (*pchar == SEPARATOR) {
		if (!(i < bufferLen - 1)) { 
			return; 
		}
		buffer[i] = *pchar;
		++pchar;
		++i;
	}

	ExpandHelper(&buffer[i], bufferLen - i, pchar);

	// add trailing dashes
	i = strlen(buffer);
	size_t strLen = strlen(str);
	for (size_t j = strLen; 
		j > 0 && 
		i < bufferLen - 1 && 
		str[j - 1] == SEPARATOR; 
		--j, ++i) 
	{
		buffer[i] = str[j - 1];
	}
	buffer[i] = '\0';
}

void ExpandHelper(char* buffer, size_t bufferLen, const char* str) {
	
	static const SEPARATOR = '-';
	
	size_t i = 0;
	const char* pchar = &str[0];
	char start = 0;
	char end = 0;
	char c = 0;

	if (!isalnum(*pchar)) return;
		
	start = *pchar;
	++pchar;

	while (1) {

		if (*pchar != SEPARATOR) break;

		++pchar;

		if (!isalnum(*pchar)) break;

		end = *pchar;
		++pchar;

		c = start;
		while (i < bufferLen - 1 && c <= end) {
			buffer[i] = c;
			++c;
			++i;
		}

		if (!(i < bufferLen - 1)) break;

		start = end + 1;
	}

	buffer[i] = '\0';

	ExpandHelper(&buffer[i], bufferLen - i, pchar);
}
