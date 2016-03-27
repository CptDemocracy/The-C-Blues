#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdbool.h>

struct LinkedList;

struct LinkedListNode {
    struct LinkedListNode* next;
    struct LinkedListNode* prev;
    void*  item;
    const struct LinkedList* _owner;
};

static int LinkedListNodeNew(struct LinkedListNode* self, 
    const struct LinkedList* owner, 
    const void* item, 
    struct LinkedListNode* next, 
    struct LinkedListNode* prev);

static void LinkedListNodeDispose(struct LinkedListNode* self);

struct LinkedList {    
    struct LinkedListNode* _first;
    struct LinkedListNode* _last;
    size_t _itemSize;
    size_t _count;
    void ( *_dispose)(void*);
};

int LinkedListNew(struct LinkedList* self, 
    size_t itemSize, 
    void (*dispose)(void*));

int LinkedListAddFirst(struct LinkedList* self, const void* item);

int LinkedListAddLast(struct LinkedList* self, const void* item);

int LinkedListRemoveFirst(struct LinkedList* self);

int LinkedListRemoveLast(struct LinkedList* self);

size_t LinkedListGetCount(struct LinkedList* self);

const struct LinkedListNode* LinkedListGetFirst(struct LinkedList* self);

const struct LinkedListNode* LinkedListGetLast(struct LinkedList* self);

int LinkedListDispose(struct LinkedList* self);

#endif /* LINKEDLIST_H */
