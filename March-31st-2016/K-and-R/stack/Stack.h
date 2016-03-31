#ifndef STACK_H
#define STACK_H

#include <stdlib.h>

struct Stack {
    void*  _items;

    // item size in bytes
    size_t _itemSize;

    // item count in items, NOT bytes
    size_t _count;

    // capacity in items, NOT bytes
    size_t _capacity; 

    // if NULL, standard free(void*) is used
    // frees contents of items but NOT the items
    // themselves
    void (*_disposeFn)(void*);
};

/* K&R C (Dennis M. Ritchie & Brian W. Kernighan)

 Exercise 4-4. Add the commands to print the top elements of the stack 
 without popping, to duplicate it, and to swap the top two elements. 
 Add a command to clear the stack. 
*/

int StackDuplicate(struct Stack* self, struct Stack* OutResult);

int StackSwapTopTwoElems(struct Stack* self);

int StackNew(struct Stack* self, size_t itemSize, void (*disposeFn)(void*));

int StackGetCount(const struct Stack* self);

int StackPush(struct Stack* self, const void* item);

int StackPop(struct Stack* self, void* OutResult);

int StackPeek(struct Stack* self, void* OutResult);

// it could possibly benefit us if we declared this as a method
// returning an int to indicate an error, however, to keep it
// compatible with void free(void*) of the standard library,
// we choose to declare it as a procedure (i.e. not returning
// any value)
void StackDispose(struct Stack* self);

#endif /* STACK_H */
