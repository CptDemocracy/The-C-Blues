/*
K.N.King "C Programming. A Modern Approach."
Programming project 1 p.311

Write a program that finds the smallest and largest in a series of words.
After the user enters the words, the program will determine which words
would come first and last if the words were listed in a dictionary order.
The program must stop accepting input when the user enters a four-letter
word. Assume that no word is more than 20 letters long. An interactive
session with the program might look like this:

"Enter word: dog
Enter word: zebra
Enter word: rabbit
Enter word: catfish
Enter word: walrus
Enter word: cat
Enter word: fish

Smallest word: cat
Largest word: zebra
"

*/

#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include <stdio.h>

#include "DynamicBuffer.h"

int main(void) {

    const static int TERMINATE_ON_LEN = 4;
    const char* PROMPT_MSG = "Please enter a word: ";

    struct DynamicBuffer dynbuffer = { 0 };
    if (DynamicBufferNew(&dynbuffer) != 0) {
        return EXIT_FAILURE;
    }
    const char* max = NULL;
    const char* min = NULL;
    const char* word = NULL;
    const char* input = NULL;

    size_t len = 0U;

    do {
        // we cannot save pointers to the smallest
        // and largest words on the spot, since they
        // will be pointing to garbage once DynamicBuffer
        // reallocates its internal buffer
        printf(PROMPT_MSG);
        input = DynamicBufferGetString(&dynbuffer);
        DynamicBufferPutChar(&dynbuffer, '\0');
    } while ((len = strlen(input)) != TERMINATE_ON_LEN);

    int i = DynamicBufferGetCount(&dynbuffer) - len - 1; 
    while (i >= 0) {

        if (i == 0) {
            word = input;
        } else if (*input == '\0') {
            word = input + 1;
        }

        if (!max && !min) {
            max = min = word;
        } else if (strcmp(word, min) < 0) {
            min = word;
        } else if (strcmp(word, max) > 0) {
            max = word;
        }

        --i; --input;
    }

    printf("Smallest word: %s\n", min);
    printf("Largest word: %s\n", max);

    DynamicBufferDispose(&dynbuffer);

    getchar();
    return EXIT_SUCCESS;
}
