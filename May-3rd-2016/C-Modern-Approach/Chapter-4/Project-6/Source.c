/*
K.N.King "C Programming. A Modern Approach."
Programming project 6 p.71

European countries use a 13-digit code, known as a European
Article Number (EAN) instead of the 12-digit Universal Product
Code (UPC) found in North America. Each AN ends with a check
digit, just as a UPC does. The technique for calculating the
check digit is also similar:

    Add the second, fourth, sixth, eight, tenth and twelfth digits.
    Add the first, third, fifth, seventh, ninth, and eleventh digits.
    Multiply the first sum by 3 and add it to the second sum.
    Subtract 1 from the total.
    Compute the remainder when the adjusted total is divided by 10.
    Subtract the remainder from 9.

For example, consider Gulluoglu Turkish Delight Pistachio & Coconut,
which has an EAN of 8691484260008. 

The first sum is: 6 + 1 + 8 + 2 + 0 + 0 = 17
The second sum is: 8 + 9 + 4 + 4 + 6 + 0 = 31
Multiplying the first sum by 3 and adding the second yield 82.
Subtracting 1 gives 81. The remainder upon dividing by 10 is 1.
When the remainder is subtracted from 9, the result is 8, which
matches the last digit of the original code. Your job is to modify
the upc.c program of Section 4.1 so that it calculates the check
digit for an EAN. The user will enter the first 12 digits of the EAN
as a single number:

"Enter the first 12 digits of an EAN: 869148426000
Check digit: 8
"

*/

#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

#define EAN_DIGIT_COUNT 12

int EanComputeCheckDigit(const char *upc, int digitCount);

int main(void) 
{
    // note that the eanDigitsArray to store the upc 
    // code is NOT intended to be null-terminated
    char eanDigitsArray[EAN_DIGIT_COUNT] = { 0 };
    int isInputValid = 0;
    int checkDigit = -1;

    printf("Please enter the first %d digits of a UPC: ", EAN_DIGIT_COUNT);

    while (!isInputValid)
    {
        isInputValid = 1;

        int i = 0;
        char c = '\0';
        while ((c = getchar()) != '\n' && c != EOF)
        {
            if (isdigit(c) && i < EAN_DIGIT_COUNT) {
                eanDigitsArray[i] = c;
                ++i;
            } else {
                // we cannot break out on the spot
                // since we still need to discard
                // the rest of invalid input
                isInputValid = 0;
            }
        }
        if (i != EAN_DIGIT_COUNT) {
            isInputValid = 0;
        }
        if (!isInputValid) {
            puts("Input invalid. Please try again.");
        }
    }
    checkDigit = EanComputeCheckDigit(eanDigitsArray, EAN_DIGIT_COUNT);
    printf("Check digit: %d\n", checkDigit);
    getchar();

    return EXIT_SUCCESS;
}

int EanComputeCheckDigit(const char *ean, int digitCount) {
    if (!ean || digitCount < 1) {
        return -1;
    }
    int sum1 = 0;
    int sum2 = 0;
    int total = 0;

    int i = 0;
    while (1) {
        if (i >= digitCount) break;
        sum1 += ean[i] - '0';
        ++i;

        if (i >= digitCount) break;
        sum2 += ean[i] - '0';
        ++i;
    }
    total = 3 * sum2 + sum1;
    return 9 - ((total - 1) % 10);
}
