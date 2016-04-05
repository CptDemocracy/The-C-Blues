#include <stdio.h>
#include "Tokenizer.h"

/* a small test program for the Tokenizer */

int main(void)
{
    size_t bufferCapacity = 256;
    char *buffer = (char*)calloc(bufferCapacity, sizeof(char));
    TokenizeExpression("1-(2+3)", buffer, bufferCapacity, 0);

    const char* token = NULL;
    token = GetNextToken();
    while (token) {
        printf("%s\n", token);
        token = GetNextToken();
    }

    printf("-----\n");

    TokenizeExpression("AAAaaa", buffer, bufferCapacity, 1);

    token = GetNextToken();
    while (token) {
        printf("%s\n", token);
        token = GetNextToken();
    }

    free(buffer);
    getchar();

    return 0;
}
