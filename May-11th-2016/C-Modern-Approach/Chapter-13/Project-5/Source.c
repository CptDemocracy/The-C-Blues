/*
K.N.King "C Programming. A Modern Approach."
Programming project 5 p.311

Write a program named sum.c that adds up its command-line arguments,
which are assumed to be integers. Running the program by typing

"sum 8 24 62"

should produce the following output:

"Total: 94"

*/

#include <stdlib.h>
#include <stdio.h>

int main(const int argc, const char* argv[]) {

    long long int sum = 0;
    long long int num = 0;
    
    // we initially assume that input is valid
    int isValid = 1;

    for (int i = 1; i < argc; ++i) {
        if ( sscanf(argv[i], " %lld", &num) != 1) {
            fprintf(stderr, "Input error. One of the arguments "
                            "is not a valid integer.\n");
            isValid = 0;
            break;
        }
        sum += num;
    }
    if (isValid) printf("Total: %lld\n", sum);

    getchar();
    return EXIT_SUCCESS;
}
