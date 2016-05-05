/*
K.N.King "C Programming. A Modern Approach."
Programming project 2 p.121

Write a program that asks the user to enter two integers,
then calculates and displays their greatest common divisor:

Enter two integers: 12 28
Greatest common divisor: 4

*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define MAX_VALUES 2

double Gcd(double m, double n);

double GcdArray(const double* nums, size_t numsSize);

int main(void) 
{
    double values[MAX_VALUES] = { 0 };
    int count = 0;
    int input = 0;

    double gcd = 1.0;

    char c = '\0';

    printf("Enter %d integers: ", MAX_VALUES);
    while (count < MAX_VALUES)
    {
        while ( scanf("%d", &input) != 1) {
            puts("Input invalid. Please try again.");    

            // reset the counter
            count = 0;

            while ( (c = getchar()) != '\n' && c != EOF) continue;
        }
        values[count] = (double)input;
        ++count;
    }
    while ( (c = getchar()) != '\n' && c != EOF) continue;

    printf("Greatest common divisor for numbers:");

    gcd = GcdArray(values, count);

    for (int i = 0; i < count; ++i) {
        printf(" %g", values[i]);
    }
    printf(";\nis %g\n", gcd);

    getchar();
    return EXIT_SUCCESS;
}

double GcdArray(const double* nums, size_t numsSize) {
    if (!nums || numsSize < 1) return 0.0;
    double gcd = nums[0];
    for (size_t i = 0; i < numsSize - 1; ++i) {
        gcd = Gcd(gcd, nums[i + 1]);
    }
    return gcd;
}

double Gcd(double m, double n) {
    double temp = 0.0;

    while (n > 0.0) {
        temp = n;
        n = fmod(m, n);
        m = temp;
    }
    return m;
}
