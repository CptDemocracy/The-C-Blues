#include <stdio.h>

/*
    Quine is a program that produced itself as output.
*/

int main(void)
{
    FILE* file = fopen(__FILE__, "r");
    if (!file) {
        fprintf(stderr, "Failed to open \"%s\"", __FILE__);
        getchar();
        return 1;
    }

    char c = '\0';
    do {
        c = fgetc(file);
        if (c == EOF) {
            break;
        }
        putchar(c);
    } while (1);

    fclose(file);
    
    getchar();

    return 0;
}
