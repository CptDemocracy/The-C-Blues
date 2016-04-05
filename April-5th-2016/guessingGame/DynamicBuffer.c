#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

#include "DynamicBuffer.h"

#define BUFFER_INIT_CAPACITY 4

static int DynamicBufferEnsureCapacity(struct DynamicBuffer* self, size_t minCapacity);

int DynamicBufferNew(struct DynamicBuffer* self) {
    if (!self) {
        errno = EINVAL;
        return EINVAL;
    }
    self->_buffer = (char*)calloc(BUFFER_INIT_CAPACITY, sizeof(char));
    if (!self->_buffer) {
        errno = ENOMEM;
        return ENOMEM;
    }
    self->_size = 0;
    self->_capacity = BUFFER_INIT_CAPACITY;
    return 0;
}

int DynamicBufferGetCount(struct DynamicBuffer* self) {
    if (!self) {
        errno = EINVAL;
        return 0;
    }
    return self->_size;
}

static int DynamicBufferEnsureCapacity(struct DynamicBuffer* self, size_t minCapacity) 
{
    if (!self || minCapacity < 1) {
        errno = EINVAL;
        return EINVAL;
    }
    if (self->_capacity < minCapacity) {
        size_t newcap
            = (self->_capacity * 2 > minCapacity) ? self->_capacity * 2 : minCapacity;
        newcap = newcap > 0 ? newcap : BUFFER_INIT_CAPACITY;
        char* newbuf = (char*)calloc(newcap, sizeof(char));
        if (!newbuf) {
            errno = ENOMEM;
            return ENOMEM;
        }
        strcpy(newbuf, self->_buffer);
        free(self->_buffer);
        self->_buffer = newbuf;
        self->_capacity = newcap;
    }
    return 0;
}

const char* DynamicBufferFGetString(struct DynamicBuffer* self, FILE* stream) {
    if (!self || !stream) {
        errno = EINVAL;
        return NULL;
    }
    char c = '\0';
    int errorCode = 0;
    
   size_t charsRead = 0;
    while ( (c = fgetc(stream)) != EOF && c != '\n') {
        // request extra byte for the null terminating character
        errorCode = DynamicBufferEnsureCapacity(self, self->_size + 2);
        if (errorCode != 0) {
            return NULL;
        }
        self->_buffer[self->_size] = c;
        ++self->_size;
		++charsRead;
    }
    return &self->_buffer[self->_size - charsRead];
}

const char* DynamicBufferGetString(struct DynamicBuffer* self) {
    if (!self) {
        errno = EINVAL;
        return NULL;
    }
    return DynamicBufferFGetString(self, stdin);
}

char DynamicBufferFGetChar(struct DynamicBuffer* self, FILE* stream) {
    if (!self || !stream) {
        errno = EINVAL;
        return '\0';
    }
    char c = '\0';
    int errorCode = 0; 
    // request extra byte for the null terminating character
    errorCode = DynamicBufferEnsureCapacity(self, self->_size + 2);
    if (errorCode != 0) {
        return '\0';
    }
    c = fgetc(stream); 
    self->_buffer[self->_size] = c;
    ++self->_size;
    return c;
}

char DynamicBufferGetChar(struct DynamicBuffer* self) {
    if (!self) {
        errno = EINVAL;
        return '\0';
    }
    return DynamicBufferFGetChar(self, stdin);
}

int DynamicBufferClear(struct DynamicBuffer* self) {
    if (!self) {
        errno = EINVAL;
        return EINVAL;
    }
    memset(self->_buffer, 0, self->_size);
    self->_size = 0;
    return 0;
}

int DynamicBufferPutChar(struct DynamicBuffer* self, char c) {
    if (!self) {
        errno = EINVAL;
        return EINVAL;
    }
    int errorCode = 0;
    // reserve an extra byte for the null terminating character
    errorCode = DynamicBufferEnsureCapacity(self, self->_size + 2);
    if (errorCode != 0) {
        return errorCode;
    }
    self->_buffer[self->_size] = c;
    ++self->_size;
    return 0;
}

int DynamicBufferPutString(struct DynamicBuffer* self, const char* s) {
    if (!self || !s) {
        errno = EINVAL;
        return EINVAL;
    }
    int errorCode = 0;
    const char* pc = &s[0];
    while (*pc) {
        // reserve an extra byte for the null terminating character
        errorCode = DynamicBufferEnsureCapacity(self, self->_size + 2);
        if (errorCode != 0) {
            return errorCode;
        }
        self->_buffer[self->_size] = *pc;
        ++self->_size;
		++pc;
    }
    return 0;
}

void DynamicBufferDispose(struct DynamicBuffer* self) {
    
    if (!self) return;

    free(self->_buffer);
    self->_buffer = NULL;
}
