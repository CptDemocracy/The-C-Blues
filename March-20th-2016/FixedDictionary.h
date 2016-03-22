#ifndef FIXEDDICTIONARY_H
#define FIXEDDICTIONARY_H

#include "Vector.h"

struct FixedDictionary {
	struct Vector** _buckets;
	size_t _count;
	size_t _capacity;
	size_t _keySize;
	size_t _valueSize;
};

int FixedDictionaryNew( struct FixedDictionary* self, 
						size_t capacity, 
						size_t keySize, 
						size_t valueSize);

int FixedDictionaryDispose(struct FixedDictionary* self);

int FixedDictionaryAdd(	struct FixedDictionary* self,
						void* key,
						void* value);

int FixedDictionaryGet(	struct FixedDictionary* self,
						void* key,
						void* OutValue);

#endif
