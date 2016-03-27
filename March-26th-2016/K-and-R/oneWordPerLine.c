#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

/* K&R C (Dennis M. Ritchie & Brian W. Kernighan)
 Exercise 1-12. Write a program that prints its input one word per line.
*/

int main(int argc, const char** argv) {

    char c;

    while (1)
    {
        printf(">>> ");
    
        while ( (c = getchar()) != '\n') {
            if (isspace(c)) {
                putchar('\n');    
            } else {
                putchar(c);
            }
        }
        putchar('\n');
    }

    return 0;
}
