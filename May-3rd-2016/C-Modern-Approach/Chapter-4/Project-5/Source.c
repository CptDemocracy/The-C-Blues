/*
K.N.King "C Programming. A Modern Approach."
Programming project 5 p.71

Rewrite the upc.c program of Section 4.1 so that the user
enters 11 digits at one time, instead of entering one digit,
then five digits, and then another five digits.

"Enter the first 11 digits of a UPC: 01380015173
Check digit: 5
"

*/

#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

#define UPC_DIGIT_COUNT 11

int UpcComputeCheckDigit(const char *upc, int digitCount);

int main(void) 
{
    // note that the upcDigitsArray to store the upc 
    // code is NOT intended to be null-terminated
    char upcDigitsArray[UPC_DIGIT_COUNT] = { 0 };
    int isInputValid = 0;
    int checkDigit = -1;

    printf("Please enter the first %d digits of a UPC: ", UPC_DIGIT_COUNT);

    while (!isInputValid)
    {
        isInputValid = 1;

        int i = 0;
        char c = '\0';
        while ((c = getchar()) != '\n' && c != EOF)
        {
            if (isdigit(c) && i < UPC_DIGIT_COUNT) {
                upcDigitsArray[i] = c;
                ++i;
            } else {
                // we cannot break out on the spot
                // since we still need to discard
                // the rest of invalid input
                isInputValid = 0;
            }
        }
        if (i != UPC_DIGIT_COUNT) {
            isInputValid = 0;
        }
        if (!isInputValid) {
            puts("Input invalid. Please try again.");
        }
    }
    checkDigit = UpcComputeCheckDigit(upcDigitsArray, UPC_DIGIT_COUNT);
    printf("Check digit: %d\n", checkDigit);
    getchar();

    return EXIT_SUCCESS;
}

int UpcComputeCheckDigit(const char *upc, int digitCount) {
    if (!upc || digitCount < 1) {
        return -1;
    }
    int sum1 = 0;
    int sum2 = 0;
    int total = 0;

    int i = 0;
    while (1) {
        if (i >= digitCount) break;
        sum1 += upc[i] - '0';
        ++i;

        if (i >= digitCount) break;
        sum2 += upc[i] - '0';
        ++i;
    }
    total = 3 * sum1 + sum2;
    return 9 - ((total - 1) % 10);
}
