/*

Algorithms in C (Sedgewick)
p.34 Chapter 3

2. Implement a routine movenexttofront(struct node* t) for a
linked list that moves the node following the node pointer to
by t to the beginning for the list.

*/

#ifdef DEBUG
    #define _CRTDBG_MAP_ALLOC
    #include <crtdbg.h>
#endif

#include <stdlib.h>
#include <stdio.h>

#include "LinkedList.h"

int LinkedListMoveNextToFront(struct LinkedList* self, struct Node* t);

int main(void) {
    
    int exitState = EXIT_SUCCESS;
    struct LinkedList list = { 0 };

    do {
        if (LinkedListNew(&list) != 0) {
            exitState = EXIT_FAILURE;
            break;
        }
        
        for (int i = 2; i >= 0; --i) {
            if (LinkedListAddFirst(&list, i) != 0) {
                exitState = EXIT_FAILURE;
                break;
            }
        }
        if (exitState == EXIT_FAILURE) break;

        struct Node 
            *first = (struct Node*)LinkedListGetFirst(&list),
            *node = first;

        while (node) {
            (void) printf("%d ", node->key);
            node = node->next;
        }
        (void) putchar('\n');

        (void) LinkedListMoveNextToFront(&list, first);
        first = (struct Node*)LinkedListGetFirst(&list);
        node = first;
        while (node) {
            (void) printf("%d ", node->key);
            node = node->next;
        }
        (void) putchar('\n');
    } while (0);

    (void) getchar();
#ifdef DEBUG
    (void) _CrtDumpMemoryLeaks();
#endif
    return exitState;
}

int LinkedListMoveNextToFront(struct LinkedList* self, struct Node* t) {
    if (!self || !t || !t->next) {
        return 1;
    }
    struct Node *head = self->_dummyHead->next,
                *next = t->next,
                *temp = NULL;

    t->next = head;
    temp = head->next;
    head->next = next->next;
    self->_dummyHead->next = next;
    next->next = temp;

    return 0;
}
