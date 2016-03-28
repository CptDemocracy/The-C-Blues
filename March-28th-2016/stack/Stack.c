#include "Stack.h"

#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define STACK_INIT_CAPACITY 4

static int EnsureCapacity(struct Stack* self, size_t minCapacity);

int StackNew(struct Stack* self, size_t itemSize, void (*disposeFn)(void*)) {
    if (!self) {
        errno = EINVAL;
        return EINVAL;
    }

    memset(self, 0, sizeof(struct Stack));

    // itemSize is unsigned which means testing
    // for a negative value is pointless, however, 
    // in case someone decides to change it to a 
    // signed integer, we test for a negative value 
    // to avoid unnecessary surprises
    if (itemSize <= 0) {
        errno = EINVAL;
        return EINVAL;
    }

    self->_items = calloc(STACK_INIT_CAPACITY, itemSize);
    if (!self->_items) {
        errno = ENOMEM;
        return ENOMEM;
    }

    self->_itemSize = itemSize;
    self->_count = 0;
    self->_capacity = STACK_INIT_CAPACITY;
    self->_disposeFn = disposeFn;

    return 0;
}

int StackGetCount(const struct Stack* self) {    
    if (!self) {
        errno = EINVAL;
        return 0;
    }
    return self->_count;
}

static int EnsureCapacity(struct Stack* self, size_t minCapacity) {
    if (!self) {
        errno = EINVAL;
        return EINVAL;
    }
    if (minCapacity > self->_capacity) {
        minCapacity = (self->_capacity * 2 > minCapacity) ? (self->_capacity * 2) : (minCapacity);
        void* newBuffer = calloc(minCapacity, self->_itemSize);
        if (!newBuffer) {
            errno = ENOMEM;
            return ENOMEM;
        }
        memcpy(newBuffer, self->_items, self->_count * self->_itemSize);
        free(self->_items);
        self->_items = newBuffer;
        self->_capacity = minCapacity;
    }
    return 0;
}

int StackPush(struct Stack* self, const void* item) {
    if (!self || !item) {
        errno = EINVAL;
        return EINVAL;
    }
    int state = EnsureCapacity(self, self->_count + 1);
    if (state != 0) {
        return state;
    }
    memcpy((char*)self->_items + self->_count * self->_itemSize, item, self->_itemSize);
    ++self->_count;
    return 0;
}

// pass NULL to OutResult if we don't care for the popped item
int StackPop(struct Stack* self, void* OutResult) {
    if (!self) {
        errno = EINVAL;
        return EINVAL;
    }

    // underflow
    if (self->_count <= 0) {
        errno = EPERM;
        return EPERM;
    }

    --self->_count;

    if (OutResult) {
        memcpy(OutResult, (char*)self->_items + self->_count * self->_itemSize, self->_itemSize);

        // Do not dispose of the dynamic memory held by the popped item
        //
        // Since we shallow-copy it to the client via OutResult, freeing
        // any memory used by the item will corrupt it for the client
    }

    return 0;
}

int StackPeek(struct Stack* self, void* OutResult) {
    if (!self) {
        errno = EINVAL;
        return EINVAL;
    }

    // empty
    if (self->_count <= 0) {
        errno = EPERM;
        return EPERM;
    }
    
    memcpy(OutResult, (char*)self->_items + (self->_count - 1) * self->_itemSize, self->_itemSize);

    return 0;
}

void StackDispose(struct Stack* self) {
    if (!self) {
        errno = EINVAL;
        return;
    }
    
    if (self->_disposeFn != NULL) {
        void* currItem = NULL;
        for (size_t i = 0; i < self->_count; ++i) 
        {
            currItem = (char*)self->_items + self->_itemSize * i;
            (*self->_disposeFn)(currItem);
        }
    }
    free(self->_items);
}
