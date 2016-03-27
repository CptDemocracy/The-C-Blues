#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "LinkedList.h"

static int LinkedListNodeNew(struct LinkedListNode* self, 
    const struct LinkedList* owner, 
    const void* item, 
    struct LinkedListNode* next, 
    struct LinkedListNode* prev)
{
    if (!self  || 
        !owner || 
        !item)
    {
        errno = EINVAL;
        return EINVAL;
    }

    self->item = calloc(1u, owner->_itemSize);
    if (!self->item) {
        errno = ENOMEM;
        return errno;
    }
    memcpy(self->item, item, owner->_itemSize);

    self->next = next;
    self->prev = prev;
    self->_owner = owner;
    
    return 0;
}

static void LinkedListNodeDispose(struct LinkedListNode* self) {
    if (!self) {
        errno = EINVAL;
        return;
    }
    void (*pDisposeFn) (void*) = NULL;
    pDisposeFn = (self->_owner->_dispose == NULL) ? free : self->_owner->_dispose;
    pDisposeFn(self->item);
}

int LinkedListNew(struct LinkedList* self, size_t itemSize, void(*dispose)(void*)) {
    if (!self) {
        errno = EINVAL;
        return EINVAL;
    }
    // unsigned can never be negative, however, in case
    // we decide to make itemSize signed in the future,
    // this will save us from nasty surprises
    if (itemSize <= 0u) {
        errno = EINVAL;
        return EINVAL;
    }
    self->_count = 0u;
    self->_first = NULL;
    self->_last  = NULL;
    self->_dispose = dispose;
    self->_itemSize = itemSize;

    return 0;
}

int LinkedListAddFirst(struct LinkedList* self, const void* item) {
    if (!self || !item) {
        errno = EINVAL;
        return EINVAL;
    }
    struct LinkedListNode* pNode = calloc(1u, sizeof(struct LinkedListNode));
    if (!pNode) {
        errno = ENOMEM;
        return ENOMEM;
    }
    if (!self->_first) {
        LinkedListNodeNew(pNode, self, item, NULL, NULL);
        self->_last = pNode;
    } else {
        LinkedListNodeNew(pNode, self, item, self->_first, NULL);
        self->_first->prev = pNode;
    }
    self->_first = pNode;
    ++self->_count;
    return 0;
}

int LinkedListAddLast(struct LinkedList* self, const void* item) {
    if (!self || !item) {
        errno = EINVAL;
        return EINVAL;
    }
    struct LinkedListNode* pNode = calloc(1u, sizeof(struct LinkedListNode));
    if (!pNode) {
        errno = ENOMEM;
        return ENOMEM;
    }
    if (!self->_first) {
        return LinkedListAddFirst(self, item);
    } else {
        LinkedListNodeNew(pNode, self, item, NULL, self->_last);
        self->_last->next = pNode;
        self->_last = pNode;
    }
    ++self->_count;
    return 0;
}

int LinkedListRemoveFirst(struct LinkedList* self) {
    if (!self) {
        errno = EINVAL;
        return EINVAL;
    }
    if (!self->_first) {
        errno = EPERM;
        return EPERM;
    }
    struct LinkedListNode* currNode = self->_first;
    self->_first = self->_first->next;
    self->_first->prev = NULL;
    LinkedListNodeDispose(currNode);
    free(currNode);
    --self->_count;
    return 0;
}

int LinkedListRemoveLast(struct LinkedList* self) {
    if (!self) {
        errno = EINVAL;
        return EINVAL;
    }
    if (!self->_last) {
        errno = EPERM;
        return EPERM;
    }
    struct LinkedListNode* currNode = self->_last;
    self->_last = self->_last->prev;
    self->_last->next = NULL;
    LinkedListNodeDispose(currNode);
    free(currNode);
    --self->_count;
    return 0;
}

int LinkedListDispose(struct LinkedList* self) {
    if (!self) {
        errno = EINVAL;
        return EINVAL;
    }
    struct LinkedListNode* pNode = self->_first;
    while (pNode) {
        struct LinkedListNode* currNode = pNode;
        pNode = pNode->next;
        LinkedListNodeDispose(currNode);
        free(currNode);
    }
    self->_count = 0u;
    return 0;
}

size_t LinkedListGetCount(struct LinkedList* self) {
    if (!self) {
        errno = EINVAL;
        return 0u;
    }
    return self->_count;
}

const struct LinkedListNode* LinkedListGetFirst(struct LinkedList* self) {
    if (!self) {
        errno = EINVAL;
        return NULL;
    }
    return self->_first;
}

const struct LinkedListNode* LinkedListGetLast(struct LinkedList* self) {
    if (!self) {
        errno = EINVAL;
        return NULL;
    }
    return self->_last;
}
