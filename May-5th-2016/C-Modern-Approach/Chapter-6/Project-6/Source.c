/*
K.N.King "C Programming. A Modern Approach."
Programming project 6 p.121

Write a program that prompts the user to enter a number n,
then prints all even squares between 1 and n. For example,
if the user enters 100, the program should print the following:

4
16
36
64
100

*/

#include <stdlib.h>
#include <stdio.h>

int main(void) 
{
    int lim = 0;
    int square = 0;
    char c = '\0';

    while (1)
    {
        printf( "Please enter a number, lower than which," 
                "you want all even squares listed: \n");
        if ( scanf("%d", &lim) != 1) {
            fprintf(stderr, "Input invalid. Please try again.\n");

            while ( (c = getchar()) != '\n' && c != EOF) continue;

            continue;
        }
        break;
    }
    while ( (c = getchar()) != '\n' && c != EOF) continue;

    int i = 2; 
    while (square < lim) {
        square = i * i;
        i += 2;

        printf("%d\n", square);
    }
    getchar();
    return EXIT_SUCCESS;
}
