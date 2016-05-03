/*
K.N.King "C Programming. A Modern Approach."
Programming project 1 p.71

Write a program that asks the user to enter a two-digit number,
then prints the number with its digits reversed. A session with
the program should have the following appearance:

Enter a two-digit number: 28
The reversal is: 82

*/

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

#define BUFFER_SIZE           16
#define INVALID_INPUT_MSG    "Input invalid. Please try again."

#define DEBUG
#undef  DEBUG

int StringReverse(char *s, int first, int last);

int main(void)
{
    char buffer[BUFFER_SIZE] = { 0 };
    const int DIGIT_COUNT = 2;

#ifdef DEBUG
    assert(DIGIT_COUNT < BUFFER_SIZE);
#endif
    int isInputValid = 0;
    
    printf("Please enter a %d-digit number: ", DIGIT_COUNT);
    while (!isInputValid)
    {
        isInputValid = 1;

        int i = 0;
        char c = '\0';
        while ((c = getchar()) != '\n' && c != EOF) 
        {
            if (isdigit(c) && i < DIGIT_COUNT) {
                buffer[i] = c;
                ++i;
            } else {
                // we cannot break out on the spot
                // because we still need to discard
                // illegal input
                isInputValid = 0;    
            }
        }
        buffer[i] = '\0';
        if (i == 0) {
            isInputValid = 0;
        }
        if (!isInputValid) {
            puts(INVALID_INPUT_MSG);
        }
    }
    StringReverse(buffer, 0, strlen(buffer) - 1);
    printf("The reversal is: %s\n", buffer);
    getchar();
    return EXIT_SUCCESS;
}

int StringReverse(char *s, int first, int last) {
    if (!s || first < 0 || last < first) {
        return 1;
    }
    char temp = '\0';
    while (first < last) 
    {
        temp     = s[first];
        s[first] = s[last];
        s[last]  = temp;

        ++first; 
        --last;
    }
    return 0;
}
