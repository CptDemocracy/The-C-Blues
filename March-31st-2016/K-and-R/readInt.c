#include <string.h>
#include <stdio.h>
#include <ctype.h>

/*K&R C (Dennis M. Ritchie & Brian W. Kernighan)
 Exercise 5-1. As written, getint treats a + or - not followed by a digit as a valid
 representation of zero. Fix it to push such a character back on the input.
*/

int ReadInt(void) {
    int value = 0;    
    int sign = 1;
    char c = 0;
    do {
        // skip whitespace
        c = getchar();
    } while (isblank(c));
    if (c == '-' || c == '+') {
        if (c == '-') {
            sign = -1;
        }
        c = getchar();
    }
    while (isblank(c)) {
        c = getchar();
    }
    while (isdigit(c)) {
        value = value * 10 + (c - '0');
        c = getchar();
    }
    // at this point we have consumed
    // a char that does not belong to
    // us - we need to return it back
    ungetc(c, stdin);

    return value * sign;
}

int main(void) {    

    char c = 0;
    int num = 0;
    printf("Please enter an integer: \n");
    while (1)
    {
        printf(">>> ");
        num = ReadInt();

        // flush redundant input
        while (c != '\n') {
            c = getchar();
        }
        c = 0;

        printf("%d\n", num);
    }

    getchar();
    return 0;
}
