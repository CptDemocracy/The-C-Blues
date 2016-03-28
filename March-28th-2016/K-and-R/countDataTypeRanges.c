#include <limits.h>
#include <stdio.h>
#include <float.h>

/* K&R C (Dennis M. Ritchie & Brian W. Kernighan)
 Exercise 2-1. Write a program to determine the ranges of char, short, int, and long
 variables, both signed and unsigned, by printing appropriate values from standard headers
 and by direct computation. Harder if you compute them: determine the ranges of the various
 floating-point types.
*/

signed char GetMaxChar(void) {
	return ((unsigned char)-1) >> 1;
}

short GetMaxShort(void) {
	return ((unsigned short)-1) >> 1;
}

int GetMaxInt(void) {
	return ((unsigned int)-1) >> 1;
}

long GetMaxLong(void) {
	return ((unsigned long)-1) >> 1;
}

long long GetMaxLongLong(void) {
	return ((unsigned long long)-1) >> 1;
}

unsigned char GetMaxUnsignedChar(void) {
	return ((unsigned char)-1);
}

unsigned short GetMaxUnsignedShort(void) {
	return ((unsigned short)-1);
}

unsigned int GetMaxUnsignedInt(void) {
	return ((unsigned int)-1);
}

unsigned long GetMaxUnsignedLong(void) {
	return ((unsigned long)-1);
}

unsigned long long GetMaxUnsignedLongLong(void) {
	return ((unsigned long long)-1);
}

float GetMaxFloat(void) {
	// IEEE754 23 bit fraction part
	unsigned long bits = ((unsigned long)-1) >> 9;

	// IEEE754 8-bit exponent
	bits = bits | ((((1 << 8) - 1) ^ 1) << 23);

	return *(float*)&bits;
}

double GetMaxDouble(void) {
	// IEEE754 52 bit fraction part
	unsigned long long bits = ((unsigned long long)-1) >> 12;

	// IEEE754 11 bit exponent
	bits = bits | ((((unsigned long long)-1) >> 1) ^ (((unsigned long long)-1) >> 11));

	return *(double*)&bits;
}

int main(void)
{
	printf("\nMax float value:\n");
	printf("\t%-14s %lf\n", "Macro:", FLT_MAX);
	printf("\t%-14s %lf\n", "Function call:", GetMaxFloat());

	printf("\nMax double value:\n");
	printf("\t%-14s %lf\n", "Macro:", DBL_MAX);
	printf("\t%-14s %lf\n", "Function call:", GetMaxDouble());

	printf("\nMax char value:\n");
	printf("\t%-14s %d\n", "Macro:", CHAR_MAX);
	printf("\t%-14s %d\n", "Function call:", GetMaxChar());

	printf("\nMax unsigned char value:\n");
	printf("\t%-14s %u\n", "Macro:", UCHAR_MAX);
	printf("\t%-14s %u\n", "Function call:", GetMaxUnsignedChar());

	printf("\nMax int value:\n");
	printf("\t%-14s %d\n", "Macro:", INT_MAX);
	printf("\t%-14s %d\n", "Function call:", GetMaxInt());

	printf("\nMax unsigned int value:\n");
	printf("\t%-14s %u\n", "Macro:", UINT_MAX);
	printf("\t%-14s %u\n", "Function call:", GetMaxUnsignedInt());

	printf("\nMax long value:\n");
	printf("\t%-14s %ld\n", "Macro:", LONG_MAX);
	printf("\t%-14s %ld\n", "Function call:", GetMaxLong());

	printf("\nMax unsigned long value:\n");
	printf("\t%-14s %lu\n", "Macro:", ULONG_MAX);
	printf("\t%-14s %lu\n", "Function call:", GetMaxUnsignedLong());

	printf("\nMax long long value:\n");
	printf("\t%-14s %lld\n", "Macro:", LLONG_MAX);
	printf("\t%-14s %lld\n", "Function call:", GetMaxLongLong());

	printf("\nMax unsigned long long value:\n");
	printf("\t%-14s %llu\n", "Macro:", ULLONG_MAX);
	printf("\t%-14s %llu\n", "Function call:", GetMaxUnsignedLongLong());
		
	getchar();
	return 0;
}
