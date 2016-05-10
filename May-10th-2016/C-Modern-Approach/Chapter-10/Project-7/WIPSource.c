/*
K.N.King "C Programming. A Modern Approach."
Programming project 7 p.239

Write a program that prompts the user for a number
and then displays the number, using characters to simulate
the effect of a seven-segment display:

"Enter a number: 491-9014
      _            _   _
|_|  |_|        | |_| | |    | |_|
  |   _|        |  _| |_|    |   |
"
Characters other than digits should be ignored. Write the program
so that the maximum number of digits is controlled by a macro named
MAX_DIGITS, which has the value 10.

*/

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#define DIGIT_BIT_COUNT  7
#define MAX_DIGITS       10

struct DigitBits 
{
    int bits[DIGIT_BIT_COUNT];
};

void DigitBitsOutput(const struct DigitBits* bits, FILE* stream);

const struct DigitBits* DigitToBits(char c);

int main(void) {

    //const char HORIZONTAL    = '_';
    //const char VERTICAL        = '|';
    //const char WHITESPACE    = ' ';

    //struct DigitBits* digits[MAX_DIGITS] = { 0 };
    const struct DigitBits* digitPtr = NULL;
    char c = '\0';
    int digitCount = 0;

    while (c != EOF)
    {
        digitCount = 0;

        while ((c = getchar()) != '\n' && c != EOF && digitCount < MAX_DIGITS) {
            digitPtr = DigitToBits(c);
            if (digitPtr) {
                //digits[digitCount] = digitPtr;
                DigitBitsOutput(digitPtr, stdout);
                ++digitCount;
            }
        }
    }
    getchar();

    return EXIT_SUCCESS;
}

void DigitBitsOutput(const struct DigitBits* digit, FILE* stream) {
    if (!digit || !stream) return;

    const static char* VERTICAL        = "|";
    const static char* HORIZONTAL    = "_";

    fprintf(stream, " %s \n"
                    "%s%s%s\n"
                    "%s%s%s\n",
        digit->bits[0] ? HORIZONTAL : " ", 
        digit->bits[1] ? VERTICAL    : " ",  
        digit->bits[2] ? HORIZONTAL : " ", 
        digit->bits[3] ? VERTICAL    : " ",  
        digit->bits[4] ? VERTICAL    : " ",  
        digit->bits[5] ? HORIZONTAL : " ", 
        digit->bits[6] ? VERTICAL    : " ");
}

const struct DigitBits* DigitToBits(char c) {
    if (!isdigit(c)) {
        return NULL;
    }

    const static struct DigitBits digits[] = { 
        [0] = {
            .bits = { [0] = 1, [1] = 1, [3] = 1, [4] = 1, [5] = 1, [6] = 1 }
        },
        [1] = {
            .bits = { [1] = 1, [4] = 1 }
        },
        [2] = {
            .bits = { [0] = 1, [2] = 1, [3] = 1, [4] = 1, [5] = 1 }
        },
        [3] = {
            .bits = { [0] = 1, [2] = 1, [3] = 1, [5] = 1, [6] = 1 }
        },
        [4] = {
            .bits = { [1] = 1, [2] = 1, [3] = 1, [6] = 1 }
        },
        [5] = {
            .bits = { [0] = 1, [1] = 1, [2] = 1, [5] = 1, [6] = 1 }
        },
        [6] = {
            .bits = { [0] = 1, [1] = 1, [2] = 1, [4] = 1, [5] = 1, [6] = 1 }
        },
        [7] = {
            .bits = { [0] = 1, [1] = 1, [4] = 1 }
        },
        [8] = {
            .bits = { [0] = 1, [1] = 1, [2] = 1, [3] = 1, [4] = 1, [5] = 1, [6] = 1 }
        },
        [9] = {
            .bits = { [0] = 1, [1] = 1, [2] = 1, [3] = 1, [5] = 1, [6] = 1 }
        }
    };

    const static struct DigitBits* DIGIT_LOOKUP_TABLE[] = {
        [0] = &digits[0],
        [1] = &digits[1],
        [2] = &digits[2],
        [3] = &digits[3],
        [4] = &digits[4],
        [5] = &digits[5],
        [6] = &digits[6],
        [7] = &digits[7],
        [8] = &digits[8],
        [9] = &digits[9]
    };

    return DIGIT_LOOKUP_TABLE[c - '0'];
}
