/*
K.N.King "C Programming. A Modern Approach."
Programming project 11 p.96

Write a program that asks the user for a two-digit number,
then prints the English word for the number:

"Enter a two-digit number: 45
You entered the number forty-five.
"
*/

#include <stdlib.h>
#include <stdio.h>

#define MAX_NUMBER 99

int main(void) 
{
    const char* numTable[MAX_NUMBER] = {
        [0] = "zero",
        [1] = "one",
        [2] = "two",
        [3] = "three",
        [4] = "four",
        [5] = "five",
        [6] = "six",
        [7] = "seven",
        [8] = "eight",
        [9] = "nine",
        [10] = "ten",
        [11] = "eleven",
        [12] = "twelve",
        [13] = "thirteen",
        [14] = "fourteen",
        [15] = "fifteen",
        [16] = "sixteen",
        [17] = "seventeen",
        [18] = "eighteen",
        [19] = "nineteen",
        [20] = "twenty",
        /* gap */
        [30] = "thirty",
        /* gap */
        [40] = "fourty",
        /* gap */
        [50] = "fifty",
        /* gap */
        [60] = "sixty",
        /* gap */
        [70] = "seventy",
        /* gap */
        [80] = "eighty",
        /* gap */
        [90] = "ninety",        
    };

    int number = 0;
    char c = '\0';

    while (1)
    {
        if ( scanf("%d", &number) != 1) 
        {
            printf ("Input invalid. Please make sure you are entering" 
                    "a positive integer below or equal to %d\n", 
                    MAX_NUMBER);
            
            while ( (c = getchar()) != '\n' && c != EOF) continue;
            continue;
        }
        while ( (c = getchar()) != '\n' && c != EOF) continue;
        if (number < 0) {
            puts("Input invalid. The number cannot be negative. Please try again.");
            continue;
        }
        if (number > MAX_NUMBER) {
            printf("Input invalid. The number cannot be greater than %d.\n", MAX_NUMBER);
            continue;
        }
        break;
    }
    
    // play it safe
    number %= 100;
        
    if (number > 20) {
        printf("%s-", numTable[number - number % 10]);
        printf("%s", numTable[number % 10]);
    } else {
        printf("%s", numTable[number]);
    }
    putchar('\n');
    

    getchar();
    return EXIT_SUCCESS;
}
