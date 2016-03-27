#define DEBUG

#ifdef DEBUG
    #define _CRTDBG_MAP_ALLOC
    #include <crtdbg.h>
    #include <stdlib.h>
#else
    #include <stdlib.h>
#endif

#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <math.h>
#include "LinkedList.h"

#define CHAR_BUFFER_SIZE 32

char CHAR_BUFFER[CHAR_BUFFER_SIZE];

void CustomDisposeFn(double* item) {
    free(item);
}

int main(void) {
    
    struct LinkedList listOfDoubles = { 0 };
    LinkedListNew(&listOfDoubles, sizeof(double), CustomDisposeFn);
    
    double i = 0.0;
    for (i = 5.0; i >= 0.0; --i) {
        LinkedListAddFirst(&listOfDoubles, &i);
    }
    for (i = 5.0; i >= 0.0; --i) {
        LinkedListAddLast(&listOfDoubles, &i);
    }
    LinkedListRemoveFirst(&listOfDoubles);
    LinkedListRemoveLast(&listOfDoubles);

    const struct LinkedListNode* pLast = LinkedListGetFirst(&listOfDoubles);
    const struct LinkedListNode* pNode = LinkedListGetLast(&listOfDoubles);
    while (pNode != pLast) {
        printf("%.1lf ", *(double*)pNode->item);
        pNode = pNode->prev;
    }
    printf("\n");

    LinkedListDispose(&listOfDoubles);

#ifdef DEBUG
    _CrtDumpMemoryLeaks();
#endif

    getchar();
    return 0;
}
