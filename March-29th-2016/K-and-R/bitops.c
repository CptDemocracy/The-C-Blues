#include <stdint.h>
#include <stdio.h>
#include <errno.h>

/* In this source file you will find exercises from K&R C - 2-6 through 2-10 */

/* K&R C (Dennis M. Ritchie & Brian W. Kernighan)
 Exercise 2-6. Write a function setbits(x,p,n,y) that returns x with the n bits 
 that begin at position p set to the rightmost n bits of y, leaving the other 
 bits unchanged. 
*/

#define SET_BITS(tovalue, bitpos, bitcount, fromvalue) \
	(((((1 << (bitcount)) - 1) << (bitpos)) & (fromvalue)) | (tovalue))

/*
 K&R C (Dennis M. Ritchie & Brian W. Kernighan)
 Exercise 2-7. Write a function invert(x,p,n) that returns x with the n bits 
 that begin at position p inverted (i.e., 1 changed into 0 and vice versa), 
 leaving the others unchanged.

*/

// LIPS programmers are gonna love this one! :-)
#define INVERT(value, bitpos, bitcount) \
	(((((1 << (bitcount)) - 1) << (bitpos)) | (value)) & \
	( ~((((1 << (bitcount)) - 1) << (bitpos)) & (value))))

/*
 K&R C (Dennis M. Ritchie & Brian W. Kernighan)
 Exercise 2-8. Write a function rightrot(x,n) that returns the value of the 
 integer x rotated to the right by n positions. 

*/
int32_t ROTR32(int32_t value, int32_t rotbits) {
	return (((uint32_t)value >> rotbits) | (value << (32 - rotbits)));
}

/*
 K&R C (Dennis M. Ritchie & Brian W. Kernighan)
 Exercise 2-9. In a two's complement number system, x &= (x-1) deletes the 
 rightmost 1-bit in x. Explain why. Use this observation to write a faster 
 version of bitcount. 

 This is not always the case. Consider a situation: x = 1 << 2 == 100(2)
 Now x - 1 == 011(2). "And"-ing x and (x - 1) - 100(2) & 011(2) will now 
 yield 0.

*/

size_t CountBitsInChar(void) {
	size_t count = 0;
	unsigned char bits = (unsigned char)-1;
	while (bits > 0) {
		bits >>= 1;
		++count;
	}
	return count;
}

size_t CountBitsInShort(void) {
	size_t count = 0;
	unsigned short bits = (unsigned short)-1;
	while (bits > 0) {
		bits >>= 1;
		++count;
	}
	return count;
}

size_t CountBitsInInt(void) {
	size_t count = 0;
	unsigned int bits = (unsigned int)-1;
	while (bits > 0) {
		bits >>= 1;
		++count;
	}
	return count;
}

size_t CountBitsInLong(void) {
	size_t count = 0;
	unsigned long bits = (unsigned long)-1;
	while (bits > 0) {
		bits >>= 1;
		++count;
	}
	return count;
}

size_t CountBitsInLongLong(void) {
	size_t count = 0;
	unsigned long long bits = (unsigned long long)-1;
	while (bits > 0) {
		bits >>= 1;
		++count;
	}
	return count;
}

/*
K&R C (Dennis M. Ritchie & Brian W. Kernighan)
Exercise 2-10. Rewrite the function lower, which converts upper case letters to lower case,
with a conditional expression instead of if-else. 

*/

int ToLower(int c) {
	return c >= 'A' && c <= 'Z' ? c + ' ' : c;
}

int main(void) {
	
	return 0;
}
