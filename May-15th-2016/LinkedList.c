#include <stdlib.h>
#include <string.h>

#include "LinkedList.h"

int LinkedListNew(struct LinkedList* self) {
    
    int exitState = 0;
    struct Node* ptr = NULL;

    do {
        if (!self) {
            exitState = 1;
            break;
        }
        ptr = (struct Node*)calloc(1, sizeof(struct Node));
        if (!ptr) {
            exitState = 2;
            break;
        }
        ptr->key = 0;
        ptr->next = NULL;
        self->_dummyHead = ptr;
    } while (0);

    return exitState;
}

void LinkedListDispose(struct LinkedList* self) {
    if (!self) {
        return;
    }
    struct Node 
        *currnode = self->_dummyHead,
        *temp = NULL;

    while (currnode) {
        temp = currnode;
        currnode = currnode->next;
        free(temp);
    }
    self->_dummyHead = NULL;
    self->_count = 0;
}

int LinkedListAddFirst(struct LinkedList* self, int key) {

    int exitState = 0;
    struct Node* node = NULL;

    do {
        if (!self) {
            exitState = 1;
            break;
        }
        node = (struct Node*)calloc(1, sizeof(struct Node));
        if (!node) {
            exitState = 2;
            break;
        }
        node->key = key;

        if (self->_dummyHead->next) {
            node->next = self->_dummyHead->next;
        } else {
            node->next = NULL;
        }
        self->_dummyHead->next = node;

        ++self->_count;
    } while (0);

    return exitState;
}

int LinkedListRemoveFirst(struct LinkedList* self) {
    if (!self || !self->_dummyHead) return 1;
    struct Node* currfirst = self->_dummyHead->next;
    if (!currfirst) {
        return 2;
    } else {
        self->_dummyHead->next = currfirst->next;
        free(currfirst);
        --self->_count;
    }
    return 0;
}

const struct Node* LinkedListGetLast(struct LinkedList* self) {
    if (!self || !self->_dummyHead) return NULL;
    struct Node* currnode = self->_dummyHead->next;
    while (currnode && currnode->next) {
        currnode = currnode->next;
    }        
    return currnode;
}

const struct Node* LinkedListFind(struct LinkedList* self, int key) {
    if (!self || !self->_dummyHead) {
        return NULL;
    }
    struct Node* currnode = self->_dummyHead->next;

    while (currnode) {
        if (currnode->key == key) {
            return currnode;
        }
        currnode = currnode->next;
    }
    return NULL;
}

size_t LinkedListGetCount(struct LinkedList* self) {
    if (!self) {
        return 0U;
    }
    return self->_count;
}

const struct Node* LinkedListGetFirst(struct LinkedList* self) {
    if (!self || !self->_dummyHead) {
        return NULL;
    }
    return self->_dummyHead->next;
}
