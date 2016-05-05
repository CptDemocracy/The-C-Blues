/*
K.N.King "C Programming. A Modern Approach."
Programming project 6 p.96

Modify the upc.c program of Section 4.1 so that
it checks whether a UPC is valid. After the user
enters a UPC, the program will display either 
VALID or NOT VALID.
*/

#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

#define UPC_DIGIT_COUNT 12

char UpcComputeCheckDigit(const char *upc, int digitCount);

int ValidateUPC(const char *upc, int fullDigitCount);

int main(void) 
{
    // note that the upcDigitsArray to store the upc 
    // code is NOT intended to be null-terminated
    char upcDigitsArray[UPC_DIGIT_COUNT] = { 0 };
    int isInputValid = 0;
    int isUPCValid = 0;

    printf("Please enter the UPC to check it for validity: ");

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
            } 
            else if (!isspace(c)) {
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
    isUPCValid = ValidateUPC(upcDigitsArray, UPC_DIGIT_COUNT);

    if (isUPCValid) {
        puts("VALID");
    }
    else {
        puts("INVALID");
    }
    getchar();

    return EXIT_SUCCESS;
}

char UpcComputeCheckDigit(const char *upc, int digitCount) {
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
    return (9 - ((total - 1) % 10)) + '0';
}

int ValidateUPC(const char *upc, int fullDigitCount) {
    if (!upc) {
        return 0;
    }
    if (fullDigitCount < 1) {
        return 0;
    }
    // UpcComputeCheckDigit takes (upcDigitCount - 1) digits represented as
    // characters since the last digit in the UPC code is supposed to be the
    // check digit
    return upc[fullDigitCount - 1] == UpcComputeCheckDigit(upc, fullDigitCount - 1);
}
