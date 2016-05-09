/*
K.N.King "C Programming. A Modern Approach."
Programming project 15 p.177

One of the oldest known encryption techniques is the
Caesar cipher, attributed to Julius Caesar. It involves
replacing each letter in a message with another letter
that is a fixed number of positions later in the alphabet.
(If the replacement would go past the letter Z, the cipher
wraps around to the beginning of the alphabet).

Write a program that encrypts a message using a Caesar
cipher.

"Enter message to be encrypted: Go ahead, make my day.
Enter shift amount (1-25): 3
Encrypted message: Jr dkhdg, pdnh pb gdb"

*/

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

#include "Queue.h"

int EncryptCaesar(const char* msg, int shift, char* OutResult);

int main(void)
{    
    char c = '\0';
    int count = 0;
    char* inputBuffer = NULL;
    int shift = 0;

    struct Queue inputCharQueue = { 0 };
    if (QueueNew(&inputCharQueue, sizeof(char)) != 0) {
        return EXIT_FAILURE;
    }
    printf("Please enter a message to be encrypted: ");

    while ((c = getchar()) != '\n' && c != EOF) {
        (void) QueueEnqueue(&inputCharQueue, &c);    
    }
    count = (int)QueueGetCount(&inputCharQueue);
    inputBuffer = (char*)calloc(count + 1, sizeof(char));
    if (!inputBuffer) {
        return EXIT_FAILURE;
    }
    for (int i = 0; i < count; ++i) {
        (void) QueueDequeue(&inputCharQueue, &inputBuffer[i]);
    }
    printf("Enter shift amount: ");
    while (scanf(" %d", &shift) != 1) {
        fprintf(stderr, "Invalid value for the shift. Please make "
                        "sure you are entering an integer value.\n");

        // discard irrelevant trailing input
        while ((c = getchar()) != '\n' && c != EOF) continue;
    }
    while ((c = getchar()) != '\n' && c != EOF) continue;
    
    EncryptCaesar(inputBuffer, shift, inputBuffer);
    printf("Encrypted message: %s\n", inputBuffer);

    free(inputBuffer);
    inputBuffer = NULL;

    QueueDispose(&inputCharQueue);

    getchar();
    return EXIT_SUCCESS;
}

int EncryptCaesar(const char* msg, int shift, char* OutResult) {
    if (!msg) {
        return 1;
    }
    if (!OutResult) {
        return 2;
    }

    const static int ALPHA_LEN = 'Z' - 'A' + 1;
    if (shift < 0) shift = ALPHA_LEN + shift;

    char c = '\0';
    int count = 0;
    int caseOffset = 0;

    while ((c = *msg) != '\0') {
        if (isalpha(c)) {

            caseOffset = isupper(c) ? 'A' : 'a';

            c = (c % caseOffset + shift) % ALPHA_LEN + caseOffset;
        }
        OutResult[count] = c;
        ++count;
        ++msg;
    }    
    return 0;
}
