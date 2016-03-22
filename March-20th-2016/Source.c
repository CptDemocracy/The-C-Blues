#ifdef DEBUG
  #define _CRTDBG_MAP_ALLOC
  #include <stdlib.h>
  #include <crtdbg.h>
#else
  #include <stdlib.h>
#endif

#include <string.h>
#include <stddef.h>
#include <stdio.h>
#include <errno.h>
#include <ctype.h>
#include <time.h>

#define _USE_MATH_DEFINES
#include <math.h>

#include "NameSpace.h"
#include "FixedDictionary.h"
#include "Temp.h"

#define CHAR_BUFFER_SIZE 64

char CHAR_BUFFER[CHAR_BUFFER_SIZE];

int main(void)
{
	const int NUM_COUNT = 10;
	
	const char* DELIMS = " ";

	const char* NUMBARS[] = {
		"zero",  "one",  "two", "three",
		"four",  "five", "six", "seven",
		"eight", "nine"
	};

	const int KEY_BUFFER_SIZE = 16;
	char* keyBuffer = (char*)calloc(KEY_BUFFER_SIZE, sizeof(char));

	struct FixedDictionary dict;
	FixedDictionaryNew(&dict, NUM_COUNT, KEY_BUFFER_SIZE, sizeof(int));

	for (int i = 0; i < NUM_COUNT; ++i) {
		memset(keyBuffer, 0, KEY_BUFFER_SIZE);

		size_t numBarLen = strlen(NUMBARS[i]);
		numBarLen = numBarLen < KEY_BUFFER_SIZE - 1U ? numBarLen : KEY_BUFFER_SIZE - 1U;

		memcpy(keyBuffer, NUMBARS[i], numBarLen);
		FixedDictionaryAdd(&dict, keyBuffer, &i);
	}

	int isValid = 1;
	while (1) {

		if (!isValid) {
			printf("Input invalid.\n");
		}
		isValid = 1;

		int i = 0;

		// we could implement a dynamic buffer for this mere demonstration
		// of a fixed dictionary we chose to supply a buffer big enough
		// to accommodate our presentation needs
		while (1) {
			char c = getchar();	
			if (c == '\0' || c == '\n') {
				break;
			}
			// if users supplied more input than we can accommodate,
			// simply flush it, and inform the users about the error,
			// so that we avoid unnecessary confusion at a later point
			// when someone's item will not be found for strange reasons
			if (i < CHAR_BUFFER_SIZE - 1) {
				CHAR_BUFFER[i] = c;
				++i;
			} else {
				// don't break!!! - we need to flush redundant input
				isValid = 0;
			}
		}
		CHAR_BUFFER[i] = '\0';

		if (!isValid) {
			continue;
		}

		char* pToken = strtok(CHAR_BUFFER, DELIMS);

		// this should never happen
		if (pToken == NULL) {
			isValid = 0;
			continue;
		}

		do {
			int inputLen = strlen(pToken);

			// trim white space in front
			// we don't care about white space at the end
			// since strtok() handled that for us already

			char* begin = pToken;
			while (begin != '\0' && isblank(*begin)) {
				++begin;
				--inputLen;
			}

			if (inputLen < 1 || inputLen > KEY_BUFFER_SIZE - 1) {
				isValid = 0;
				continue;
			}

			int value = 0;	
			memset(keyBuffer, 0, KEY_BUFFER_SIZE);		
			memcpy(keyBuffer, begin, inputLen);

			int found = FixedDictionaryGet(&dict, keyBuffer, &value);
			if (found) {
				printf("%d ", value);	
			}
			else {
				printf("\nWe apologize, but %s was not found in the dictionary.\n", keyBuffer);
			}

			pToken = strtok(NULL, DELIMS);
		} while (pToken != NULL);			
		printf("\n");
	}
		
	FixedDictionaryDispose(&dict);

	free(keyBuffer);

#ifdef DEBUG
	_CrtDumpMemoryLeaks();
#endif

	getchar();
	return 0;
}
