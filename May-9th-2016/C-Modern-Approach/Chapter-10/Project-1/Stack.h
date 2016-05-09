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

struct Stack
{
    void*   _items;
    size_t  _itemSize;
    size_t  _itemCount;
    size_t  _itemCapacity;
    void (*disposeFn)(void*);
};

int StackNew(struct Stack* self, size_t itemSize, void (*disposeFn)(void*));

void StackDispose(struct Stack* self);

size_t StackGetCount(struct Stack* self);

int StackPeek(struct Stack* self, void* OutResult);

int StackPush(struct Stack* self, const void* item);

int StackPop(struct Stack* self, void* OutResult);
