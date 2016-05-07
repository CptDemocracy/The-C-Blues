/*
K.N.King "C Programming. A Modern Approach."
Programming project 13 p.157

"Enter a sentence: It was deja vu all over again.
Average word length: 3.4"

*/

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

// No, we will make it more challenging - we will not consider 
// a punctuation mark to be part of the word for simplicity.

#define BUFFER_SIZE 256

int main(void)
{    
    char buffer[BUFFER_SIZE] = { 0 };
    double avgWordLen = 0.0;
    size_t wordLen = 0;
    size_t wordCount = 0;

    printf("Please enter a sentence: ");

    if (!fgets(buffer, BUFFER_SIZE, stdin)) {
        return EXIT_FAILURE;
    }
    // we can detect if users entered more characters than
    // BUFFER_SIZE by checking the last non-null character
    // of the user input string, if it is not a new line
    // character, users entered more data than provided for,
    // which means we have trailing characters in the stream
    // we should discard
    if (buffer[strlen(buffer) - 1] != '\n') {
        char c = '\0';
        while ( (c = getchar()) != '\n' && c != EOF) continue;
    }

    // tokenize user input
    char *pchar = buffer;
    while (*pchar != '\0') {
        if (isalnum(*pchar) && !isalnum(*(pchar + 1))) {
            *(pchar + 1) = '\0';
            ++pchar;

            ++wordCount;
        }
        ++pchar;
    }
    pchar = buffer;
    for (size_t i = 0; i < wordCount; ++i) {
        // skip past non-alnum characters in 
        // the beginning of a token
        while (*pchar && !isalnum(*pchar)) ++pchar;

        wordLen = strlen(pchar);
        avgWordLen += wordLen;

        // move to the next token
        pchar = &pchar[wordLen + 1];
    }
    avgWordLen /= (double)wordCount;

    printf("Average word length: %g\n", avgWordLen);
    getchar();
    return EXIT_SUCCESS;
}
