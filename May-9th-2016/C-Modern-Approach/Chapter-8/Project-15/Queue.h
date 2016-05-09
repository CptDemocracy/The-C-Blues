#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>

struct Queue {
    size_t _itemSize;
    size_t _count;
    size_t _capacity;
    size_t _headIndex;
    size_t _tailIndex;
    void*  _items;
};

int QueueNew(struct Queue* self, size_t itemSize);

void QueueDispose(struct Queue* self);

int QueueEnqueue(struct Queue* self, const void* item);

int QueueDequeue(struct Queue* self, void* OutResult);

size_t QueueGetCount(struct Queue* self);

#endif /* QUEUE_H */
