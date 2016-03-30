#include "FixedDictionary.h"

#include <errno.h>
#include <string.h>
#include <stdlib.h>

#define DEFAULT_FIXED_DICTIONARY_CAPACITY 4

static size_t FixedDictionaryHashFn(const void* item, size_t itemSize) 
{
    if (!item) {
        errno = EINVAL;
        return 0U;
    }

    // Technically speaking, size_t can't be negative,
    // since it's unsigned. What we do want to safeguard
    // against, is the value of 0.
    //
    // The reason we test it as (less than or equal to zero)
    // is to facilitate switching types from size_t to any
    // other signed integer type, if the need arises.
    if (itemSize <= 0U) {
        errno = EINVAL;
        return 0U;
    }
    int bufferSizeBytes = itemSize + sizeof(int) - itemSize % sizeof(size_t);
    void* buffer = calloc(bufferSizeBytes, 1);
    
    // do not proceed if calloc failed
    if (!buffer) {
        errno = ENOMEM;
        return 0U;
    }
    memcpy(buffer, item, itemSize);
    
    size_t* begin = (size_t*)(buffer);
    size_t* end   = (size_t*)((char*)buffer + bufferSizeBytes);
    
    size_t hashCode = 0;
    for (size_t* pntr = begin; pntr < end; ++pntr) {
        hashCode ^= (*pntr);
    }

    free(buffer);
    return hashCode;
}

struct Slot {
    void* key;
    void* value;
    size_t hashCode;
    struct FixedDictionary* owner;
};

static int SlotNew( struct Slot* self,
                    struct FixedDictionary* owner,
                    void* key,
                    void* value,
                    size_t hashCode)
{
    if (!self  ||
        !owner ||
        !key   ||
        !value) 
    {
        errno = EINVAL;
        return EINVAL;
    }

    size_t keySize   = owner->_keySize;
    size_t valueSize = owner->_valueSize;

    self->key = calloc(1, keySize);
    if (!self->key) {
        errno = ENOMEM;
        return ENOMEM;
    }
    memcpy(self->key, key, keySize);

    self->value = calloc(1, valueSize);
    if (!self->value) {

        free(self->key);

        errno = ENOMEM;
        return ENOMEM;
    }
    memcpy(self->value, value, valueSize);

    self->owner = owner;
    self->hashCode = hashCode;

    return 0;
}

static int SlotDispose(struct Slot* self)
{
    if (!self) {
        errno = EINVAL;
        return EINVAL;
    }
    free(self->key);
    free(self->value);
    return 0;
}

int FixedDictionaryNew( struct FixedDictionary* self, 
                        size_t capacity, 
                        size_t keySize, 
                        size_t valueSize)
{
    if (!self) {
        errno = EINVAL;
        return EINVAL;
    }

    // Technically speaking, size_t can't be negative,
    // since it's unsigned. What we do want to safeguard
    // against, is the value of 0.
    //
    // The reason we test it as (less than or equal to zero)
    // is to facilitate switching types from size_t to any
    // other signed integer type, if the need arises.

    if (capacity  <= 0U ||
        keySize   <= 0U ||
        valueSize <= 0U) 
    {
        errno = EINVAL;
        return EINVAL;
    }
    
    capacity = capacity > DEFAULT_FIXED_DICTIONARY_CAPACITY ? 
        capacity : DEFAULT_FIXED_DICTIONARY_CAPACITY;
    
    // Initialize an array of pointers to Vectors holding our
    // bucket collisions to zero.
    // It is of utmost importance that we initialize pointers
    // to zero, since our item lookup logic will rely on it.
    self->_buckets = calloc(capacity, sizeof(struct Vector*));
    if (!self->_buckets) {
        errno = ENOMEM;
        return ENOMEM;
    }

    self->_capacity = capacity;
    self->_count = 0;
    self->_keySize = keySize;
    self->_valueSize = valueSize;

    return 0;
}

int FixedDictionaryDispose(struct FixedDictionary* self)
{
    if (!self) {
        errno = EINVAL;
        return EINVAL;
    }
    free(self->_buckets);
    return 0;
}

int FixedDictionaryAdd( struct FixedDictionary* self,
                        void* key,
                        void* value)
{
    if (!self ||
        !key  ||
        !value) 
    {
        errno = EINVAL;
        return EINVAL;
    }

    if (self->_count >= self->_capacity) {
        errno = EINVAL;
        return EINVAL;
    }

    size_t hashCode = FixedDictionaryHashFn(key, self->_keySize);
    size_t bucketIndex = hashCode % self->_capacity;

    if (self->_buckets[bucketIndex] == NULL) {
        self->_buckets[bucketIndex] = calloc(1, sizeof(struct Vector));
        VectorNew(self->_buckets[bucketIndex], sizeof(struct Slot), NULL);
    }
    else {
        size_t collCount = VectorGetCount(self->_buckets[bucketIndex]);
        for (size_t i = 0; i < collCount; ++i) {
            struct Slot slot;
            VectorGet(self->_buckets[bucketIndex], i, &slot);
            if (memcmp(slot.key, key, self->_keySize) == 0) {
                return 0;
            }
        }
    }

    struct Slot slot;
    SlotNew(&slot, self, key, value, hashCode);
    VectorAdd(self->_buckets[bucketIndex], &slot);
    ++self->_count;

    return 1;
}

int FixedDictionaryGet(    struct FixedDictionary* self,
                        void* key,
                        void* OutValue) 
{    
    if (!self ||
        !key) 
    {
        errno = EINVAL;
        return EINVAL;
    }

    size_t hashCode = FixedDictionaryHashFn(key, self->_keySize);
    size_t bucketIndex = hashCode % self->_capacity;

    struct Vector* bucket = self->_buckets[bucketIndex];
    if (!bucket) {
        return 0;
    }

    size_t collCount = VectorGetCount(bucket);
    for (size_t i = 0; i < collCount; ++i) {
        struct Slot slot;
        VectorGet(bucket, i, &slot);
        if (slot.hashCode == hashCode) {
            if (memcmp(slot.key, key, self->_keySize) == 0) {
                memcpy(OutValue, slot.value, self->_valueSize);
                return 1;
            }
        }
    }
    return 0;
}
