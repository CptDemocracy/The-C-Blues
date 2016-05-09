/*
K.N.King "C Programming. A Modern Approach."
Programming project 16 p.177

Write a program that tests whether two words are anagrams 
(permutations of the same letters):

"Enter first word: smartest
Enter second word: mattress
The words are anagrams

Enter first word: dumbest
Enter second word: stumble
The words are not anagrams.
"

*/

#include <stdlib.h>
#include <limits.h>
#include <stdio.h>

#include "Queue.h"

int AreAnagrams(const char* s1, const char* s2);

int main(void)
{    
    char c = '\0';
    char* firstWord = NULL;
    char* secondWord = NULL;

    int count = 0;
    int areAnagrams = 0;

    struct Queue inputCharQueue = { 0 };
    if (QueueNew(&inputCharQueue, sizeof(char)) != 0) {
        return EXIT_FAILURE;
    }

    printf("Please enter the first word: ");
    while ((c = getchar()) != '\n' && c != EOF) {
        (void) QueueEnqueue(&inputCharQueue, &c);
    }
    count = QueueGetCount(&inputCharQueue);
    
    firstWord = (char*)calloc(count + 1, sizeof(char));
    if (!firstWord) {
        return EXIT_FAILURE;
    }

    for (int i = 0; i < count; ++i) {
        QueueDequeue(&inputCharQueue, &firstWord[i]);
    }

    printf("Please enter the second word: ");
    while ((c = getchar()) != '\n' && c != EOF) {
        (void) QueueEnqueue(&inputCharQueue, &c);
    }
    count = QueueGetCount(&inputCharQueue);

    secondWord = (char*)calloc(count + 1, sizeof(char));
    if (!secondWord) {
        return EXIT_FAILURE;
    }

    for (int i = 0; i < count; ++i) {
        QueueDequeue(&inputCharQueue, &secondWord[i]);
    }

    areAnagrams = AreAnagrams(firstWord, secondWord);

    printf(
        "\"%s\" and \"%s\" are %sanagrams.\n", 
        firstWord, 
        secondWord, 
        areAnagrams ? "" : "not ");
    
    free(firstWord);
    firstWord = NULL;

    free(secondWord);
    secondWord = NULL;

    QueueDispose(&inputCharQueue);

    getchar();
    return EXIT_SUCCESS;
}

int AreAnagrams(const char* s1, const char* s2) {
    if (!s1) {
        return 1;
    }
    if (!s2) {
        return 2;
    }    
    char lookupTable[UCHAR_MAX] = { 0 };    

    char c = '\0';
    int count1 = 0;
    int count2 = 0;

    while ((c = *s1++) != '\0') {
        lookupTable[c] = 1;
        ++count1;
    }
    while ((c = *s2++) != '\0') {
        if (count1 == count2 || lookupTable[c] == 0) {
            return 0;
        }
        ++count2;
    }
    return 1;
}
