/*
K.N.King "C Programming. A Modern Approach."
Programming project 1 p.239

1. Modify the stack example of Section 10.2 so that it stores
chracters instead of integers. Next, add a main function that
asks the user to enter a series of parentheses and/or braces,
then indicates whether or not they're properly nested:

"Enter parentheses and/or braces: ((){}{()})
Parentheses/braces are nested properly
"

*/

#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "Stack.h"

const static int STACK_INIT_CAPACITY = 4;

const static int STACK_SUCCESS                   = 0;
const static int STACK_INVALID_ARGUMENT_ERROR    = 1;
const static int STACK_OUT_OF_MEMORY_ERROR       = 2;
const static int STACK_UNDERFLOW_ERROR           = 3;
const static int STACK_OVERFLOW_ERROR            = 4; /* unused */
const static int STACK_INVALID_OPERATION_ERROR   = 5;

static int StackEnsureCapacity(struct Stack* self, size_t minCapacity) {
    if (!self) {
        errno = EINVAL;
        return STACK_INVALID_ARGUMENT_ERROR;
    }
    if (minCapacity < 1) {
        errno = EINVAL;
        return STACK_INVALID_ARGUMENT_ERROR;
    }
    if (minCapacity > self->_itemCapacity) {
        minCapacity = minCapacity > self->_itemCapacity * 2 ? minCapacity : self->_itemCapacity * 2;
        void* newItems = calloc(minCapacity, self->_itemSize);
        if (!newItems) {
            errno = ENOMEM;
            return STACK_OUT_OF_MEMORY_ERROR;
        }
        memcpy(newItems, self->_items, self->_itemCount * self->_itemSize);
        free(self->_items);

        self->_items = newItems;
        self->_itemCapacity = minCapacity;
    }

    return STACK_SUCCESS;
}

int StackNew(struct Stack* self, size_t itemSize, void (*disposeFn)(void*)) {
    if (!self) {
        errno = EINVAL;
        return STACK_INVALID_ARGUMENT_ERROR;
    }
    if (itemSize < 1) {
        errno = EINVAL;
        return STACK_INVALID_ARGUMENT_ERROR;
    }

    self->_items = calloc(STACK_INIT_CAPACITY, itemSize);
    if (!self->_items) {
        errno = ENOMEM;
        return STACK_OUT_OF_MEMORY_ERROR;
    }
    self->_itemCapacity = STACK_INIT_CAPACITY;
    self->_itemCount = 0;
    self->_itemSize = itemSize;
    self->disposeFn = disposeFn;

    return STACK_SUCCESS;
}

void StackDispose(struct Stack* self) {
    if (!self) {
        errno = EINVAL;
        return;
    }
    if (self->disposeFn != NULL) {
        void* item = NULL;
        size_t count = self->_itemCount;
        for (size_t i = 0U; i < count; ++i) {
            item = (char*)self->_items + i * self->_itemSize;
            self->disposeFn(item);
        }
    }
    free(self->_items);
    self->_items = NULL;
}

size_t StackGetCount(struct Stack* self) {
    if (!self) {
        errno = EINVAL;
        return 0U;
    }
    return self->_itemCount;
}

int StackPeek(struct Stack* self, void* OutResult) {
    if (!self) {
        errno = EINVAL;
        return STACK_INVALID_ARGUMENT_ERROR;
    }
    if (!OutResult) {
        errno = EINVAL;
        return STACK_INVALID_ARGUMENT_ERROR;
    }
    if (self->_itemCount < 1) {
        errno = EPERM;
        return STACK_INVALID_OPERATION_ERROR;
    }
    void* item = NULL;

    item = (char*)self->_items + self->_itemSize * (self->_itemCount - 1);
    memcpy(OutResult, item, self->_itemSize);

    return STACK_SUCCESS;
}

int StackPush(struct Stack* self, const void* item) {
    if (!self) {
        errno = EINVAL;
        return STACK_INVALID_ARGUMENT_ERROR;
    }
    if (!item) {
        errno = EINVAL;
        return STACK_INVALID_ARGUMENT_ERROR;
    }
    
    int error = 0;
    error = StackEnsureCapacity(self, self->_itemCount + 1);
    if (error) {
        return error;
    }
    void* copyToAddr = NULL;
    copyToAddr = (char*)self->_items + self->_itemCount * self->_itemSize;

    memcpy(copyToAddr, item, self->_itemSize);
    ++self->_itemCount;

    return STACK_SUCCESS;    
}

int StackPop(struct Stack* self, void* OutResult) {
    if (!self) {
        errno = EINVAL;
        return STACK_INVALID_ARGUMENT_ERROR;
    }
    if (self->_itemCount < 1) {
        errno = EPERM;
        return STACK_UNDERFLOW_ERROR;
    }
    void* popAddr = NULL;
    popAddr = (char*)self->_items + self->_itemSize * (self->_itemCount - 1);

    if (OutResult) {
        memcpy(OutResult, popAddr, self->_itemSize);
    } else if (self->disposeFn != NULL) {
        self->disposeFn(popAddr);
    }
    --self->_itemCount;

    return STACK_SUCCESS;
}
