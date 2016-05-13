#ifndef Dictionary_H
#define Dictionary_H

#include "Vector.h"

struct Dictionary {
    struct Vector** _buckets;
    size_t _count;
    size_t _capacity;
    size_t _keySize;
    size_t _valueSize;
};

int DictionaryNew(  struct Dictionary* self, 
                    size_t capacity, 
                    size_t keySize, 
                    size_t valueSize);

void DictionaryDispose(struct Dictionary* self);

int DictionaryAdd(  struct Dictionary* self,
                    const void* key,
                    const void* value);

int DictionaryGet(  const struct Dictionary* self,
                    const void* key,
                    void* OutValue);

int DictionaryContains( const struct Dictionary* self,
                        const void* key);

#endif
