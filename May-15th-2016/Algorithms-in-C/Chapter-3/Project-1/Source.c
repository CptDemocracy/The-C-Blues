/*

Algorithms in C (Sedgewick)
p.34 Chapter 3

Write a program to fill in a two-dimensional array of boolean values
by setting a[i][j] to 1 if the greatest common divisor of i and j is
1 and to 0 otherwise.

*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define ROW_COUNT (16)
#define COL_COUNT (16)
#define COL_WIDTH (3)

int Gcd(int m, int n);

int main(void) {

    int table[ROW_COUNT][COL_COUNT] = { 0 };

    // fill the table
    for (int i = 0; i < ROW_COUNT; ++i) {
        for (int j = 0; j < COL_COUNT; ++j) {
            table[i][j] = ( Gcd(i, j) == 1);
        }
    }

    // display the table
    for (int i = 0; i < ROW_COUNT; ++i) {
        for (int j = 0; j < COL_COUNT; ++j) {
            (void) printf("%*d", COL_WIDTH, table[i][j]);
        }
        (void) putchar('\n');
    }
    (void) getchar();
    
    return EXIT_SUCCESS;
}

int Gcd(int m, int n) {

    int temp = 0;

    m = abs(m);
    n = abs(n);

    while (n > 0) {
        temp = n;
        n = m % n;
        m = temp;
    }
    return m;
}
