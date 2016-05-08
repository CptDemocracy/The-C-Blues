/*
K.N.King "C Programming. A Modern Approach."
Programming project 14 p.177

Write a program that reverses the words in a sentence:

"Enter a sentence: you can cage a swallow, can't you?
Reversal of sentence: you can't swallow a cage can you?

*/

#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

#include "Queue.h"

int main(void)
{    
    char c = '\0';
    char punct = '\0';
    char* substrPtr = NULL;
    int i = 0;

    struct Queue inputCharQueue = { 0 };
    if (QueueNew(&inputCharQueue, sizeof(char)) != 0) {
        return EXIT_FAILURE;
    }
    while ( (c = getchar()) != '\n' && c != EOF) {
        if (!(ispunct(c) && c != '\'')) (void)QueueEnqueue(&inputCharQueue, &c);
    }
    
    int count = (int)QueueGetCount(&inputCharQueue);
    char* buffer = (char*)calloc(count + 1, sizeof(char));
    if (!buffer) {
        return EXIT_FAILURE;
    }

    i = 0;
    while (i < count) {
        (void)QueueDequeue(&inputCharQueue, &buffer[i]);
        ++i;
    }    

    substrPtr = &buffer[count];
    i = count;

    while (i >= 0) 
    {
        *substrPtr = '\0';        

        while (i >= 0 && isspace(*substrPtr)) {
            --substrPtr;
            --i;
        }
        while (i >= 0 && !isspace(*substrPtr)) {
            --substrPtr;
            --i;
        }
        printf("%s ", substrPtr + 1);        
    }
    putchar('\n');

    free(buffer);
    buffer = NULL;

    QueueDispose(&inputCharQueue);

    getchar();
    return EXIT_SUCCESS;
}
