#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include <stdlib.h>

struct Node {
    int key;
    struct Node* next;
};

struct LinkedList {
    struct Node* _dummyHead;
    size_t _count;
};

int LinkedListNew(struct LinkedList* self);

void LinkedListDispose(struct LinkedList* self);

int LinkedListAddFirst(struct LinkedList* self, int key);

int LinkedListRemoveFirst(struct LinkedList* self);

size_t LinkedListGetCount(struct LinkedList* self);

const struct Node* LinkedListGetFirst(struct LinkedList* self);

const struct Node* LinkedListGetLast(struct LinkedList* self);

const struct Node* LinkedListFind(struct LinkedList* self, int key);

#endif /* LINKEDLIST_H_ */
