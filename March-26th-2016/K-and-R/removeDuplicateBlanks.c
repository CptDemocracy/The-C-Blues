#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

/* K&R C (Dennis M. Ritchie & Brian W. Kernighan)
 Exercise 1-9. Write a program to copy its input to its output, 
 replacing each string of one or more blanks by a single blank.
*/

int main(int argc, const char** argv) {

    char currc, prevc;

    while (1) 
    {
        printf(">>> ");
    
        currc = getchar();
        prevc = 0;
        while (currc != '\n') {

            // I agree, this test is too "hackish", however,
            // what it simply does, is it checks whether IF
            // NOT current char is whitespace AND the previous
            // char was whitespace as well, if yes, we print
            // the character to the output, if not, we ignore
            // it
            //
            // !(prevc ^ currc) can be simplified as 
            // (prevc ^ currc) == 0, if it's 0, then prev char
            // was the same char as the current one (in our case,
            // both were whitespace). Why? Because XOR is similar
            // to OR, except that if we XOR two set bits, it will
            // return 0. If two values are the same, XORing them
            // will produce a zero

            if (!(isblank(currc) && !(prevc ^ currc))) {
                putchar(currc);
            }
            prevc = currc;
            currc = getchar();
        }
        
        putchar('\n');
    }

    return 0;
}
