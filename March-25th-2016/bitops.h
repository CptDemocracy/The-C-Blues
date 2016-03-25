#ifndef BITOPS_H
#define BITOPS_H

// a nifty utility that tells you whether your setup
// performs an arithmetic or a logical right shift;
// implemented as a macro
#define IS_RSH_LOGICAL() ((-2 >> 1) != (-1))

// count the number of bits in an integer
// implemented as a macro
#define BIT_SIZE(type, resultVarName)		\
	do {									\
			type x = (type)1;				\
			resultVarName = 1;				\
			while(x <<= 1) ++resultVarName; \
	} while (0)

// show us if given type is signed
// implemented as a macro
// cool lil' trick I learned about from Peter van der Linden's "Expert C Programming"
#define IS_SIGNED(type) ((type)-1 < 0)

// unwieldy experimental x8086-ish ROTL functionality implementation
// as a macro
// NOTE, signed or not, this implementation works both for logical right shifts
// and arithmetic right shifts
#define ROTL(type, value, resultVarName)	\
	do {									\
		int bcount = 0;						\
		BIT_SIZE((type), (bcount));			\
		resultVarName = ((((value) >> ((bcount) - 1)) & 1) | ((value) << 1)); \
	} while (0)

// ditto, ROTR
// NOTE, signed or not, this implementation works both for logical right shifts
// and arithmetic right shifts
#define ROTR(type, value, resultVarName)	\
	do {									\
		int bcount = 0;						\
		BIT_SIZE((type), (bcount));			\
		resultVarName = (((value) >> 1) & ~((1 << ((bcount) - 1)))) | ((value) << ((bcount) - 1));	\
	} while (0)

// returns true if all ON bits in the bitPattern
// are ON in the value as well
#define HAS_ALL_BITS_ON(value, bitPattern) \
	(((value) & (bitPattern)) == (value))

// returns true if the bit at position bitPos
// is ON in the value
// please NOTE that positioning starts at 0,
// i.e. first bit position is at 0, second at 1,
// and so on
#define IS_BIT_ON(value, bitPos) \
	((value) & (1 << (bitPos)))

// extracts bitCount bits starting at bitPos in the 
// value, returns the bits with the first bit that
// was at bitPos, now as an LSB (the 0th bit), e.g.
// 
// EXTRACT_BITS(64, 5, 2);
//
// 64(10) has a bit pattern of 01000000(2)
// we request 2 bits at position 5, which
// is 10(2) == 2(10), hence the result is 
// 2(10);
//
// implemented as a macro
#define EXTRACT_BITS(value, bitPos, bitCount) \
	(((value) & (((1 << (bitCount)) - 1) << (bitPos))) >> (bitPos))

// takes bits from bitPattern starting at position bitPos
// in the number of bitCount, and sets these bits in the
// value.
// 
// implemented as a macro
#define SET_BITS(value, bitPattern, bitPos, bitCount) \
	((value) | ((bitPattern) & (((1 << (bitCount)) - 1) << (bitPos))))

// return the bit position of a bit pattern in 
// value or -1 if no such bit pattern is present
// in the value
static inline int FindBitPattern(int value, int bitPattern) {
	
	const int NOT_FOUND = -1;

	if (!bitPattern && !value) {
		return 0;
	}
	else if (!bitPattern) {
		return NOT_FOUND;
	}

	int bitPos = 0;
	while (value >= bitPattern) {
		if ((value & bitPattern) == bitPattern) {
			return bitPos;
		}
		value >>= 1;
		++bitPos;
	}
	return NOT_FOUND;
}

#endif /* BITOPS_H */
