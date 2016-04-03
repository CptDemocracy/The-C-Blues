#include <string.h>
#include <errno.h>

#include "Queue.h"

#define QUEUE_INIT_CAPACITY 4

static int QueueEnsureCapacity(struct Queue* self, size_t minCapacity);

int QueueNew(struct Queue* self, size_t itemSize) {
    if (!self || itemSize < 1) {
        errno = EINVAL;
        return EINVAL;
    }
    
    self->_items = calloc(QUEUE_INIT_CAPACITY, itemSize);
    if (!self->_items) {
        errno = ENOMEM;
        return ENOMEM;
    }

    self->_itemSize = itemSize;
    self->_count = 0;
    self->_capacity = QUEUE_INIT_CAPACITY;
    self->_headIndex = 0;
    self->_tailIndex = 0;

    return 0;
}

void QueueDispose(struct Queue* self) {
    
    if (!self) return;
    
    free(self->_items); 
    self->_items = NULL;
}

int QueueEnqueue(struct Queue* self, const void* item) {
    if (!self || !item) {
        errno = EINVAL;
        return EINVAL;
    }
    int errorCode = 0;    
    errorCode = QueueEnsureCapacity(self, self->_count + 1);
    if (errorCode != 0) {
        return errorCode;
    }
    void* tail = (char*)self->_items + self->_tailIndex * self->_itemSize;
    memcpy(tail, item, self->_itemSize);
    self->_tailIndex = (self->_tailIndex + 1) % self->_capacity;
    ++self->_count;
    return errorCode;
}

int QueueDequeue(struct Queue* self, void* OutResult) {
    if (!self || !OutResult) {
        errno = EINVAL;
        return EINVAL;
    }
    if (self->_count < 1) {
        errno = EPERM;
        return EPERM;
    }
    void* head = (char*)self->_items + self->_headIndex * self->_itemSize;    
    memcpy(OutResult, head, self->_itemSize);

    // sanitize the dequeued item in the container
    memset(head, 0, self->_itemSize);

    self->_headIndex = (self->_headIndex + 1) % self->_capacity;
    --self->_count;
    return 0;
}

size_t QueueGetCount(struct Queue* self) {
    if (!self) {
        errno = EINVAL;
        return EINVAL;
    }
    return self->_count;
}

static int QueueEnsureCapacity(struct Queue* self, size_t minCapacity) {
    if (!self || minCapacity < 1) {
        errno = EINVAL;
        return EINVAL;
    }
    if (self->_capacity < minCapacity) {
        minCapacity = (self->_capacity * 2 > minCapacity) ? self->_capacity * 2 : minCapacity;
        void* newItems = calloc(minCapacity, self->_itemSize);
        if (!newItems) {
            errno = ENOMEM;
            return ENOMEM;
        }
        size_t firstChunkCount = self->_capacity - (self->_headIndex + self->_count) % self->_capacity;
        memcpy(newItems, (char*)self->_items + self->_headIndex, firstChunkCount * self->_itemSize);
        
        self->_headIndex = 0;

        size_t secondChunkCount = self->_count - firstChunkCount;
        memcpy((char*)newItems + firstChunkCount, self->_items, secondChunkCount * self->_itemSize);
        
        self->_tailIndex = self->_headIndex + self->_count;

        free(self->_items);
        self->_items = newItems;
        self->_capacity = minCapacity;
    }
    return 0;
}
