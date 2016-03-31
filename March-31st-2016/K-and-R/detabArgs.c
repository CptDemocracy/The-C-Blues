#include <stdlib.h>
#include <stdio.h>

/*K&R C (Dennis M. Ritchie & Brian W. Kernighan)
 Exercise 5-12. Extend entab and detab to accept the shorthand

    detab -m +n

 to mean tab stops every n columns, starting at column m. Choose 
 convenient (for the user) default behavior.
*/

#define DEFAULT_START_TABS      4
#define DEFAULT_COLS_PER_TAB    4

int main(int argc, const char** argv) {

    if (argc > 1 && argc != 3) {
        fprintf(stderr, "Usage: detab [-start +colspertab]\n");
        return 1;
    }

    int starttabs = DEFAULT_START_TABS;
    int colspertab = DEFAULT_COLS_PER_TAB;    

    if (argc == 3) {
        starttabs = atoi(argv[1]);
        if (starttabs < 1) {
            fprintf(stderr, "the start argument must be greater than zero\n");
            return 1;
        }
        colspertab = atoi(argv[2]);
        if (colspertab < 1) {
            fprintf(stderr, "the cols per tab argument must be greater than zero\n");
            return 1;
        }
    }

    int tabcount = starttabs;
    int count = 0;
    char c = 0;
    
    while (1) {
        count = 0;
        printf(">>> ");
        tabcount = starttabs;
        while ( (c = getchar()) != '\n') {
            if (c == '\t') {                
                for (int i = 0; i < tabcount - count; ++i) {
                    putchar(' ');
                }
                tabcount = colspertab;
            }
            putchar(c);
            count = (count + 1) % tabcount;            
        }
        putchar('\n');        
    }

    return 0;
}
