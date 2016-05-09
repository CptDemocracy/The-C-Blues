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
#include <stdio.h>

#include "Queue.h"
#include "Stack.h"

int AreParensValid(const char* text);

int main(void)
{
    struct Queue inputCharQueue = { 0 };
    if (QueueNew(&inputCharQueue, sizeof(char)) != 0) {
        return EXIT_FAILURE;
    }

    printf("Please enter parentheses and/or braces: ");

    char c = '\0';
    while ((c = getchar()) != '\n') {
        if (c == EOF) {
            fprintf(stderr, "Error occured when reading input. Please try again.\n");
        }
        QueueEnqueue(&inputCharQueue, &c);
    }

    int inputCount = 0;
    inputCount = QueueGetCount(&inputCharQueue);

    char* buffer = (char*)calloc(inputCount + 1, sizeof(char));
    if (!buffer) {
        return EXIT_FAILURE;
    }
    for (int i = 0; i < inputCount; ++i) {
        QueueDequeue(&inputCharQueue, &buffer[i]);
    }
    buffer[inputCount] = '\0';

    int isValid = 0;
    isValid = AreParensValid(buffer);
    printf("Parentheses/braces are %snested properly.\n", isValid ? "" : "not ");

    free(buffer);
    QueueDispose(&inputCharQueue);

    getchar();
    return EXIT_SUCCESS;
}

int AreParensValid(const char* text) {
    if (!text) {
        return 0;
    }
    const static char LPAREN_LOOKUP_TABLE[UCHAR_MAX] = {
        ['('] = ')',
        ['['] = ']',
        ['{'] = '}'
    };

    const static char RPAREN_LOOKUP_TABLE[UCHAR_MAX] = {
        [')'] = '(',
        [']'] = '[',
        ['}'] = '{'
    };

    struct Stack parensCharStack = { 0 };
    if (StackNew(&parensCharStack, sizeof(char), NULL) != 0) {
        return 0;
    }

    int isValid = 1;
    char lparen = '\0';
    char c = '\0';

    while ((c = *text++) != '\0' && isValid) {
        if (LPAREN_LOOKUP_TABLE[c]) {
            (void) StackPush(&parensCharStack, &c);
        }
        else if (RPAREN_LOOKUP_TABLE[c]) {
            if (StackGetCount(&parensCharStack) < 1) {
                isValid = 0;
            } else {
                (void) StackPop(&parensCharStack, &lparen);
                if (LPAREN_LOOKUP_TABLE[lparen] != c) {
                    isValid = 0;
                }
            }
        }
    }
    isValid = isValid && StackGetCount(&parensCharStack) == 0;
    StackDispose(&parensCharStack);
    return isValid;
}
