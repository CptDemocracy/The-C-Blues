/*
K.N.King "C Programming. A Modern Approach."
Programming project 4 p.311

Write a program named reverse.c that echoes its command-line
arguments in reverse order. Running the program by typing

"reverse void and null"

should produce the following output:

"null and void"

*/

#include <stdlib.h>
#include <stdio.h>

int main(const int argc, const char* argv[]) {
    
    for (int i = argc - 1; i > 0; --i) {
        printf("%s ", argv[i]);
    }
    putchar('\n');

    getchar();
    return EXIT_SUCCESS;
}
