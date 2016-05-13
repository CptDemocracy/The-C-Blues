#include "Dictionary.h"

#include <errno.h>
#include <string.h>
#include <stdlib.h>

#define DEFAULT_FIXED_DICTIONARY_CAPACITY 4

static size_t DictionaryHashFn(const void* item, size_t itemSize) 
{
    if (!item) {
        errno = EINVAL;
        return 0U;
    }
    if (itemSize < 1U) {
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
    (void) memcpy(buffer, item, itemSize);
    
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
    const struct Dictionary* owner;
};

static int SlotNew( struct Slot* self,
                    const struct Dictionary* owner,
                    const void* key,
                    const void* value,
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
    (void) memcpy(self->key, key, keySize);

    self->value = calloc(1U, valueSize);
    if (!self->value) {

        free(self->key);

        errno = ENOMEM;
        return ENOMEM;
    }
    (void) memcpy(self->value, value, valueSize);

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

static int DictionaryEnsureCapacity(  struct Dictionary* self,
                                      size_t minCapacity)
{
    if (!self || minCapacity < 1U) {
        errno = EINVAL;
        return EINVAL;
    }

    if (self->_capacity < minCapacity) 
    {
        minCapacity = (self->_capacity * 2 < minCapacity) ? (minCapacity) : (self->_capacity * 2);
        
        struct Vector** newBuckets = (struct Vector**)calloc(minCapacity, sizeof(struct Vector*));
        if (!newBuckets) {
            errno = ENOMEM;
            return ENOMEM;
        }

        struct Slot slot = { 0 };
        int errcode = 0;

        for (size_t i = 0U; i < self->_capacity; ++i) {
            size_t bucketCount = VectorGetCount(self->_buckets[i]);
            for (size_t j = 0U; j < bucketCount; ++j) {
                (void) VectorGet(self->_buckets[i], j, &slot);
                
                size_t bucketIndex = slot.hashCode % minCapacity;
                if (newBuckets[bucketIndex] == NULL) {
                    errcode = VectorNew(newBuckets[bucketIndex], sizeof(struct Slot), NULL);                    
                }
                if (!errcode) {
                    errcode = VectorAdd(newBuckets[bucketIndex], &slot);
                }
                if (errcode) break;        
            }
        }

        if (errcode) {
            for (size_t i = 0U; i < minCapacity; ++i) {
                if (newBuckets[i]) {
                    size_t bucketCount = VectorGetCount(newBuckets[i]);
                    for (size_t j = 0U; j < bucketCount; ++j) {
                        (void) VectorDispose(newBuckets[i]);
                    }
                }
            }
            free(newBuckets);
        } else {
            for (size_t i = 0U; i < self->_capacity; ++i) {
                if (self->_buckets[i]) {
                    (void) VectorDispose(self->_buckets[i]);
                }
            }
            free(self->_buckets);

            self->_buckets = newBuckets;
            self->_capacity = minCapacity;
        }
    }

    return 0;
}

int DictionaryNew(  struct Dictionary* self, 
                    size_t capacity, 
                    size_t keySize, 
                    size_t valueSize)
{
    if (!self) {
        errno = EINVAL;
        return EINVAL;
    }

    if (capacity  < 1U ||
        keySize   < 1U ||
        valueSize < 1U) 
    {
        errno = EINVAL;
        return EINVAL;
    }
    
    capacity = capacity > DEFAULT_FIXED_DICTIONARY_CAPACITY ? 
        capacity : DEFAULT_FIXED_DICTIONARY_CAPACITY;
    
    // Initialize an array of pointers to Vectors holding our
    // bucket collisions to zero.
    // It is of utmost importance that we initialize pointers
    // to zero, since our item lookup logic relies on it.
    self->_buckets = (struct Vector**)calloc(capacity, sizeof(struct Vector*));
    if (!self->_buckets) {
        errno = ENOMEM;
        return ENOMEM;
    }

    self->_capacity = capacity;
    self->_count = 0U;
    self->_keySize = keySize;
    self->_valueSize = valueSize;

    return 0;
}

void DictionaryDispose(struct Dictionary* self)
{
    if (!self) {
        errno = EINVAL;
        return;
    }
    for (size_t i = 0U; i < self->_capacity; ++i) {
        if (self->_buckets[i]) {
            (void) VectorDispose(self->_buckets[i]);
        }
    }
    free(self->_buckets);
}

int DictionaryAdd(  struct Dictionary* self,
                    const void* key,
                    const void* value)
{
    if (!self ||
        !key  ||
        !value) 
    {
        errno = EINVAL;
        return 0;
    }

    if (DictionaryContains(self, key)) {
        return 0;
    }

    int errcode = 0;

    errcode = DictionaryEnsureCapacity(self, self->_capacity + 1);
    if (errcode) {
        return 0;
    }

    size_t hashCode = DictionaryHashFn(key, self->_keySize);
    size_t bucketIndex = hashCode % self->_capacity;

    if (self->_buckets[bucketIndex] == NULL) {
        self->_buckets[bucketIndex] = (struct Vector*)calloc(1U, sizeof(struct Vector));
        if (!self->_buckets[bucketIndex]) {
            errno = ENOMEM;
            return 0;
        }
        errcode = VectorNew(self->_buckets[bucketIndex], sizeof(struct Slot), NULL);
        if (errcode) {
            free(self->_buckets[bucketIndex]);
            return errcode;
        }
    }        

    struct Slot slot = { 0 };
    errcode = SlotNew(&slot, self, key, value, hashCode);
    if (errcode) {
        return errcode;
    }
    errcode = VectorAdd(self->_buckets[bucketIndex], &slot);
    if (errcode) {
        return errcode;
    }
    ++self->_count;

    return 1;
}

int DictionaryGet(  const struct Dictionary* self,
                    const void* key,
                    void* OutValue) 
{    
    if (!self ||
        !key  ||
        !OutValue) 
    {
        errno = EINVAL;
        return EINVAL;
    }

    size_t hashCode = DictionaryHashFn(key, self->_keySize);
    size_t bucketIndex = hashCode % self->_capacity;

    struct Vector* bucket = self->_buckets[bucketIndex];
    if (!bucket) {
        return 0;
    }

    struct Slot slot = { 0 };
    size_t collCount = VectorGetCount(bucket);
    for (size_t i = 0; i < collCount; ++i) {
        (void) VectorGet(bucket, i, &slot);
        if (slot.hashCode == hashCode) {
            if (memcmp(slot.key, key, self->_keySize) == 0) {
                (void) memcpy(OutValue, slot.value, self->_valueSize);
                return 1;
            }
        }
    }
    (void) memset(OutValue, 0, self->_valueSize);
    return 0;
}

int DictionaryContains( const struct Dictionary* self,
                        const void* key) 
{
    if (!self || !key) {
        errno = EINVAL;
        return 0;
    }

    struct Slot slot = { 0 };

    size_t hashCode = DictionaryHashFn(key, self->_keySize);
    size_t bucketIndex = hashCode % self->_capacity;

    if (self->_buckets[bucketIndex] != NULL) {
        size_t collCount = VectorGetCount(self->_buckets[bucketIndex]);
        for (size_t i = 0; i < collCount; ++i) {
            (void) VectorGet(self->_buckets[bucketIndex], i, &slot);
            if (memcmp(slot.key, key, self->_keySize) == 0) {
                return 1;
            }
        }
    }
    
    return 0;
}
