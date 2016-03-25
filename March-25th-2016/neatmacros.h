#ifndef NEATMACROS_H
#define NEATMACROS_H

#include <ctype.h>

#define MIN3(a, b, c) \
	(((a) < (b)) ? (((a) < (c)) ? (a) : (c)) : (((b) < (c)) ? (b) : (c)))

#define MAX3(a, b, c) \
	(((a) > (b)) ? (((a) > (c)) ? (a) : (c)) : (((b) > (c)) ? (b) : (c)))

#define ASCII_IS_UPPER_CASE(character) \
	(character >= 'A' && character <= 'Z')

#define ASCII_IS_LOWER_CASE(character) \
	(character >= 'a' && character <= 'z')

// ASCII_TO_UPPER macro
// experimental 
// for practical purposes, please consider using
// toupper(int) function from <ctype.h>
#define ASCII_TO_UPPER(str) \
	{ \
		char* pChar = (str); \
		while (*pChar)	\
		{	\
			*pChar = ASCII_IS_LOWER_CASE(*pChar) ? (*pChar - (char)' ') : (*pChar);	\
			++pChar;	\
		}	\
	}

// ASCII_TO_LOWER macro
// experimental 
// for practical purposes, please consider using
// tolower(int) function from <ctype.h>
#define ASCII_TO_LOWER(str) \
	{ \
		char *pChar = (str); \
		while (*pChar)	\
		{	\
			*pChar = ASCII_IS_UPPER_CASE(*pChar) ? (*pChar + (char)' ') : (*pChar); \
			++pChar;	\
		}	\
	}

#define ASCII_IS_ALPHABETIC(character) \
	(((character) >= 'A') && ((character) <= 'Z')) || \
	(((character) >= 'a') && ((character) <= 'z'))

#define ASCII_IS_DIGIT(character) \
	(((character) >= '0') && ((character) <= '9')))

#define ASCII_IS_SPECIAL(character) \
	((!ASCII_IS_ALPHABETIC(character)) && (!ASCII_IS_DIGIT(character)))

#define ABS(value) \
	(((value) > 0) ? (value) : ((value) * (-1)))

#endif /* NEATMACROS_H */
