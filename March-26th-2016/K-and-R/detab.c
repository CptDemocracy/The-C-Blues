#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <errno.h>

/* K&R C (Dennis M. Ritchie & Brian W. Kernighan)
 Exercise 1-20. Write a program detab that replaces tabs in the input with the proper number
 of blanks to space to the next tab stop. Assume a fixed set of tab stops, say every n columns.
 Should n be a variable or a symbolic parameter?

 - n should be a constant local automatic variable, global vars are generally, 
   a poor practice, however, for this implementation we chose to make n a macro 
   - named CHARS_PER_TAB_STOP, this will cause no overhead for initialization and
   provide access to all parties within the module involved
*/

#define CHARS_PER_TAB_STOP 20

int main(int argc, const char** argv) {

    int count = 0;
    char c = 0;

    while (1) {
        count = 0;
        printf(">>> ");
        while ( (c = getchar()) != '\n') {
            if (c == '\t') {
                for (int i = 0; i < CHARS_PER_TAB_STOP - count; ++i) {
                    putchar(' ');
                }
            }
            putchar(c);
            count = (count + 1) % CHARS_PER_TAB_STOP;
        }
        putchar('\n');
    }

    return 0;
}
