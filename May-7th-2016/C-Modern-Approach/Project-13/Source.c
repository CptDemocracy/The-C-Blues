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

int main(void)
{    
    char userInput[] = "It was deja vu all over again."; // should be supplied by the user
    double avgWordLen = 0.0;
    size_t wordLen = 0;
    size_t wordCount = 0;

    // tokenize user input
    char *pchar = userInput;
    while (*pchar != '\0') {
        if (isalnum(*pchar) && !isalnum(*(pchar + 1))) {
            *(pchar + 1) = '\0';
            ++pchar;

            ++wordCount;
        }
        ++pchar;
    }
    pchar = userInput;
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
