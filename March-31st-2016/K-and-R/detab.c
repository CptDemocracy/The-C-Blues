#include <stdlib.h>
#include <stdio.h>

/*K&R C (Dennis M. Ritchie & Brian W. Kernighan)
 Exercise 5-11. Modify the program entab and detab (written as exercises in 
 Chapter 1) to accept a list of tab stops as arguments. Use the default tab 
 settings if there are no arguments.
*/

int main(int argc, const char** argv) {

    if (argc < 2) {
     fprintf(stderr, "Usage detab tabwidth1 tabwidth2 ... tabwidthn");
     return 1;
    }
    int arg = 1;
    int tabcount = 1;
    int count = 0;
    char c = 0;
    
    while (1) {
        tabcount = atoi(argv[arg]);
        tabcount = tabcount > 0 ? tabcount : 1;
        count = 0;
        printf(">>> ");
        while ( (c = getchar()) != '\n') {
            if (c == '\t') {
                for (int i = 0; i < tabcount - count; ++i) {
                    putchar(' ');
                }
            }
            putchar(c);
            count = (count + 1) % tabcount;
        }
        putchar('\n');
        arg = (arg + 1) % argc;
        arg = arg > 0 ? arg : 1;
    }

    return 0;
}
