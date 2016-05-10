#ifndef DYNAMICBUFFER_H
#define DYNAMICBUFFER_H

#include <stdlib.h>
#include <stdio.h>

struct DynamicBuffer {
    char* _buffer;
    size_t _size;
    size_t _capacity;
};

int DynamicBufferGetCount(struct DynamicBuffer* self);

int DynamicBufferNew(struct DynamicBuffer* self);

const char* DynamicBufferFGetString(struct DynamicBuffer* self, FILE* stream);

const char* DynamicBufferGetString(struct DynamicBuffer* self);

char DynamicBufferFGetChar(struct DynamicBuffer* self, FILE* stream);

char DynamicBufferGetChar(struct DynamicBuffer* self);

int DynamicBufferClear(struct DynamicBuffer* self);

int DynamicBufferPutChar(struct DynamicBuffer* self, char c);

int DynamicBufferPutString(struct DynamicBuffer* self, const char* s);

void DynamicBufferDispose(struct DynamicBuffer* self);

#endif /* DYNAMICBUFFER_H */
