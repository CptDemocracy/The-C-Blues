#ifndef ROT_H
#define ROT_H

#include <stdint.h>


uint64_t ROTR64U(uint64_t uword64);

uint64_t ROTL64U(uint64_t uword64);

uint32_t ROTR32U(uint32_t uword32);

uint32_t ROTL32U(uint32_t uword32);

uint16_t ROTR16U(uint16_t uword16);

uint16_t ROTL16U(uint16_t uword16);

uint8_t ROTR8U(uint8_t uword8);

uint8_t ROTL8U(uint8_t uword8);

#endif /* ROT_H */
