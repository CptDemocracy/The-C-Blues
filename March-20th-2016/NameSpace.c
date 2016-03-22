#include "NameSpace.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <math.h>
#include <float.h>

static void PrintName(const char* name, FILE* stream) 
{
	if (!name || !stream) {
		errno = EINVAL;
		return;
	}
	fprintf(stream, "My name is %s.\n", name);
}

static double ReadDouble(FILE* stream, void(*onInvalidInput)(void)) 
{
	const int DEFAULT_BUFFER_CAPACITY = 4;
	const int CAPACITY_MULTIPLIER	  = 2;
	const double RETURN_VAL_ON_ERROR  = 0.0;

	if (!stream) {
		errno = EINVAL;
		return RETURN_VAL_ON_ERROR;
	}

	double result = 0.0;

	char* buffer = calloc(DEFAULT_BUFFER_CAPACITY, sizeof(char));
	if (!buffer) {
		errno = ENOMEM;
		return RETURN_VAL_ON_ERROR;
	}

	int capacity = DEFAULT_BUFFER_CAPACITY;
	int isValid  = 0;

	while (!isValid) 
	{
		isValid = 1;

		int count = 0;

		char c;
		while ((c = fgetc(stream)) != EOF && c != '\0' && c != '\n') {
			// skip whitespace
			if (isblank(c)) { 
				continue;
			}

			// test character
			// skip character if illegal
			if (!isdigit(c) && c != 'E' && c != 'e' && c != '+' && c != '-' && c != '.') {
				isValid = 0;
				continue;
			}

			// remember we need an extra byte to store the null-terminator
			// we account for it in this test
			if (count >= capacity - 1) {
				capacity  = (capacity > 0) ? capacity * CAPACITY_MULTIPLIER : DEFAULT_BUFFER_CAPACITY;
				char* newBuffer = calloc(capacity, sizeof(char));
				if (!newBuffer) {
					errno = ENOMEM;
					return RETURN_VAL_ON_ERROR;
				}
				memcpy(newBuffer, buffer, count);
				free(buffer);
				buffer = newBuffer;
			}
			buffer[count] = c;
			++count;
		}

		// redundant since we use calloc, however we keep it here for safety,
		// if someone changes calloc to malloc in the future
		buffer[count] = '\0';
		++count;
	
		// if empty, input is invalid
		if (count < 2) {
			isValid = 0;
		}		

		if (isValid) {
			// make sure the entirety of input has been consumed
			// if not, means input had illegal format
			char* pParseEnd = NULL;
			result = strtod(buffer, &pParseEnd);
			// if valid, *pParseEnd should point to the null-terminator
			// of the buffer
			if (pParseEnd != &buffer[count - 1]) {
				isValid = 0;
			}
			// if result overflows, strtod sets errno to ERANGE
			// we want to catch that
			if (errno == ERANGE) {
				isValid = 0;
			}
		}
		
		if (!isValid && onInvalidInput) {
			onInvalidInput();
		}
	}
	
	return result;
}

static int CountWords(FILE* stream) {
	if (!stream) {
		errno = EINVAL;
		return 0;
	}

	int count = 0;
	
	char c;
	while (1) {
		c = fgetc(stream);
		if (isalnum(c)) {
			++count;
			while (isalnum(c)) {
				c = fgetc(stream);
			}
		}
		if (c == EOF || c == '\0') {
			break;
		}
	}
	return count;
}

static int IsWordIn(FILE* stream, int (*isWord)(const char*)) {
	if (!stream || !isWord) {
		errno = EINVAL;
		return 0;
	}
	
	const int DEFAULT_BUFFER_CAPACITY = 4;
	const int CAPACITY_MULTIPLIER	  = 2;

	char* buffer = calloc(DEFAULT_BUFFER_CAPACITY, sizeof(char));
	if (!buffer) {
		errno = ENOMEM;
		return 0;
	}
	int capacity = DEFAULT_BUFFER_CAPACITY;	
	int count = 0;

	char c;
	while ((c = fgetc(stream)) != EOF && c != '\0') {

		// test character
		if (!isblank(c) && !isalnum(c)) { 
			continue;
		}

		// remember we need an extra byte to store the null-terminator
		// we account for it in this test
		if (count >= capacity - 1) {
			capacity  = (capacity > 0) ? capacity * CAPACITY_MULTIPLIER : DEFAULT_BUFFER_CAPACITY;
			char* newBuffer = calloc(capacity, sizeof(char));
			if (!newBuffer) {
				errno = ENOMEM;
				return 0;
			}
			memcpy(newBuffer, buffer, count);
			free(buffer);
			buffer = newBuffer;
		}
		buffer[count] = c;
		++count;
	}

	// redundant since we use calloc, however we keep it here for safety,
	// if someone changes calloc to malloc in the future
	buffer[count] = '\0';
	++count;

	char* word = strtok(buffer, " ");
	while (word != NULL) {
		if (isWord(word)) {
			return 1;
		}
		word = strtok(NULL, " ");		
	}
	return 0;
}

int IsPrime(long int num) {
	if (num < 2) {
		return 0;
	}
	if (num & 1) {
		long int limit = (long int)sqrt(num);
		long int divisor = 3L;
		while (divisor <= limit) {
			if ((num % divisor) == 0) {
				return 0;
			}
			divisor += 2;
		}
		return 1;
	}
	return num == 2L;
}

const struct NameSpace ns = {
	.PrintName   = PrintName,
	.ReadDouble  = ReadDouble,
	.CountWords  = CountWords,
	.IsWordIn	 = IsWordIn,
	.IsPrime	 = IsPrime,
};
