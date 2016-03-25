#include "rot.h"


uint64_t ROTR64U(uint64_t uword64) {
	return (uword64 >> 1ULL) | (uword64 << 63ULL);
}

uint64_t ROTL64U(uint64_t uword64) {
	return (uword64 << 1ULL) | (uword64 >> 63ULL);
}

uint32_t ROTR32U(uint32_t uword32) {
	return (uword32 >> 1U) | (uword32 << 31U); 
}

uint32_t ROTL32U(uint32_t uword32) {
	return (uword32 << 1U) | (uword32 >> 31U);
}

uint16_t ROTR16U(uint16_t uword16) {
	return (uword16 >> 1U) | (uword16 << 15U);
}

uint16_t ROTL16U(uint16_t uword16) {
	return (uword16 << 1U) | (uword16 >> 15U);
}

uint8_t ROTR8U(uint8_t uword8) {
	return (uword8 >> 1U) | (uword8 << 7U);
}

uint8_t ROTL8U(uint8_t uword8) {
	return (uword8 << 1U) | (uword8 >> 7U);
}
