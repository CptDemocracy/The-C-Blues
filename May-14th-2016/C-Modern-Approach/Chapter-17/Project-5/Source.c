/*
K.N.King "C Programming. A Modern Approach."
Programming project 1 p.453

Write a program that sorts a series of words entered by the user:

"Enter word: foo
Enter word: bar
Enter word: baz
Enter word: quux
Enter word:

In sorted order: bar baz foo quux
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include "DynamicBuffer.h"
#include "Vector.h"

int IsStringEmpty(const char* s);

int StrCmp(const char** ptr1, const char** ptr2);

int main(void) {

    struct DynamicBuffer dynBuffer = { 0 };
    struct Vector inputCharVector = { 0 };
    const char* userInput = NULL;
    char* temp = NULL;
    int exitState = EXIT_SUCCESS;

    if (DynamicBufferNew(&dynBuffer) != 0) {
        exitState = EXIT_FAILURE;
        return exitState;
    }

    if (VectorNew(&inputCharVector, sizeof(char*), NULL) != 0) {
        DynamicBufferDispose(&dynBuffer);
        return exitState;
    }

    while (1) 
    {
        (void) printf("Please enter word: ");

        userInput = DynamicBufferGetString(&dynBuffer);
        if (!userInput) {
            exitState = EXIT_FAILURE;
            break;
        }
        if (IsStringEmpty(userInput)) {
            break;
        }
        size_t inputCount = DynamicBufferGetCount(&dynBuffer);
        temp = (char*)calloc(inputCount + 1, sizeof(char));
        if (!temp) {
            exitState = EXIT_FAILURE;
            return exitState;
        }
        (void) strcpy(temp, userInput);
        (void) VectorAdd(&inputCharVector, &temp);
        (void) DynamicBufferClear(&dynBuffer);
    }

    size_t wordCount = VectorGetCount(&inputCharVector);

    char** words = (char**)calloc(wordCount, sizeof(char*));
    if (!words) {
        exitState = EXIT_FAILURE;
        return exitState;
    }

    for (size_t i = 0U; i < wordCount; ++i) {
        (void) VectorGet(&inputCharVector, i, &words[i]);
    }

    qsort(words, wordCount, sizeof(char*), StrCmp);

    for (size_t i = 0U; i < wordCount; ++i) {
        (void) printf("%s\n", words[i]);
    }

    free(words);

    for (size_t i = 0U; i < wordCount; ++i) {
        (void) VectorGet(&inputCharVector, i, &temp);
        free(temp);
    }
    VectorDispose(&inputCharVector);
    DynamicBufferDispose(&dynBuffer);
    
    (void) getchar();

    return exitState;
}

int IsStringEmpty(const char* s) {
    if (!s) return 0;

    char c = '\0';
    while ((c = *s) != '\0' && isspace(c)) ++s;

    return *s == '\0';
}

int StrCmp(const char** ptr1, const char** ptr2) {
    return strcmp(*ptr1, *ptr2);
}
