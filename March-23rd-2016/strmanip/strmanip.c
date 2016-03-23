#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include "strmanip.h"

static int KMP(const char* text, int textLen, const char* pattern, int patternLen);
static int* KMPCalculateDFA(const char* pattern, int patternLen, int** pOutResultDFA);

int CountWords(const char* text) {
	
	if (!text) {
		errno = EINVAL;
		return -1;
	}

	int count = 0;
	const char* pChar = text;
	while (*pChar != '\0') {
		while (isblank(*pChar)) {
			++pChar;
		}
		if (*pChar == '\0') {
			break;
		}
		++count;
		while (*pChar != '\0' && !isblank(*pChar)) {
			++pChar;
		}
	}
	return count;
}

int Substring(const char* text, int start, int count, char* OutResult) {
	if (!text) {
		errno = EINVAL;
		return 0;
	}
	if (!OutResult) {
		errno = EINVAL;
		return 0;
	}
	int i = 0;
	while (i < count) {
		if (text[start + i] == '\0') {
			break;
		}
		OutResult[i] = text[start + i];
		++i;
	}
	OutResult[i] = '\0';
	return i;
}

int IsSubstringOf(const char* target, const char* substring) {
	if (!target) {
		errno = EINVAL;
		return 0;
	}
	if (!substring) {
		errno = EINVAL;
		return 0;
	}	
	return KMP(target, strlen(target), substring, strlen(substring)) >= 0;
}

int FindString(const char* target, const char* substring) {
	// Did a research on the KMP to guarantee an O(n) time complexity
	// Used the following code for reference:
	//		code.activestate.com/recipes/577908-implementation-of-knuthmorrispratt-algorithm
	// Had to memorize it by rote to understand. The concept itself is fairly straightforward
	// but the implementation can be quite tricky.
	// Tweaked the code a little bit to avoid passing dynamic memory between functions
	// which, I believe, can easily complicate the code readability and maintenance.
	// Whenever possible, make it each function's responsibility to deallocate the dynamic
	// memory it requested.

	const int ERROR = -2;

	if (!target) {
		errno = EINVAL;
		return ERROR;
	}
	if (!substring) {
		errno = EINVAL;
		return ERROR;
	}
	return KMP(target, strlen(target), substring, strlen(substring));
}

static int* KMPCalculateDFA(const char* pattern, int patternLen, int** pOutResultDFA) {
	// NULL passed instead of a cstring
	if (!pattern) {
		errno = EINVAL;
		return NULL;
	}
	// argument out of range
	if (patternLen <= 0) {
		errno = EINVAL;
		return NULL;
	}
	// NULL passed instead of a pointer to the DFA table
	if (!pOutResultDFA) {
		errno = EINVAL;
		return NULL;
	}
	int* dfa = *pOutResultDFA;
	int k  = -1;
	dfa[0] = k;
	for (int i = 1; i < patternLen; ++i) {
		while (k > -1 && pattern[i] != pattern[k + 1]) {
			k = dfa[k];
		}
		if (pattern[i] == pattern[k + 1]) {
			++k;
		}
		dfa[i] = k;
	}
	return dfa;
}

static int KMP(const char* text, int textLen, const char* pattern, int patternLen) {

	const int NOT_FOUND = -1;
	const int ERROR		= -2;

	// NULL instead of a cstring
	if (!text) {
		errno = EINVAL;
		return ERROR;
	}
	// out of range
	if (textLen < 0) {
		errno = EINVAL;
		return ERROR;
	}
	// okay, but return NOT FOUND
	if (textLen == 0) {
		return NOT_FOUND;
	}
	// NULL instead of a cstring
	if (!pattern) {
		errno = EINVAL;
		return ERROR;
	}
	// we do not allow empty pattern lengths
	// and treat them illegal as well as negative 
	// ones
	if (patternLen <= 0) {
		errno = EINVAL;
		return ERROR;
	}
	int* dfa = calloc(patternLen, sizeof(int));
	if (!dfa) {
		errno = ENOMEM;
		return ERROR;
	}

	if (!KMPCalculateDFA(pattern, patternLen, &dfa)) {
		free(dfa);
		return ERROR;
	}

	int k = -1;
	for (int i = 0; i < textLen; ++i) {
		while (k > -1 && text[i] != pattern[k + 1]) {
			k = dfa[k];
		}
		if (text[i] == pattern[k + 1]) {
			++k;
		}
		if (k == patternLen - 1) {
			free(dfa);
			return i - k;
		}
	}
	free(dfa);
	return NOT_FOUND;
}

int RemoveString(char* text, int start, int count) {

	const int ERROR = -2;

	if (!text) {
		errno = EINVAL;
		return ERROR;
	}
	
	if (start < 0) {
		errno = EINVAL;
		return ERROR;
	}

	if (count < 0) {
		errno = EINVAL;
		return ERROR;
	}

	size_t textLen = strlen(text);

	if (start + count > textLen) {
		errno = EINVAL;
		return ERROR;
	}

	// we allow clients to call this function with arguments to 
	// start and count equal to zero, which renders memcpy or 
	// strcpy or strncpy a no-no, consider a call:
	//		RemoveString(cstr, 0, 0);
	// then memmove will be called like this:
	//		memmove(&text[0], &text[0 + 0], 0 * sizeof(char))
	// this will cause data to overlap
	memmove(&text[start], 
			&text[start + count], 
			count * sizeof(char));
	
	int endIndex   = textLen - count;
	text[endIndex] = '\0';
	
	// sanitize the non-overwritten end of the string
	// to prevent loitering
	memset(&text[endIndex], 0, count);

	return 0;
}

