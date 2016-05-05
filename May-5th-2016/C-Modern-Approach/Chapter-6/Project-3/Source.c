/*
K.N.King "C Programming. A Modern Approach."
Programming project 3 p.121

Write a program that asks the user to enter a fraction,
then reduces the fraction to lowest terms:

Enter a fraction: 6/12
In lowest terms: 1/2

*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

struct Fraction {
    int num;
    int denom;
};

int FractionReduce(
    const struct Fraction* fract, 
    struct Fraction* OutResult);

double Gcd(double m, double n);

int main(void) 
{
    struct Fraction 
        input   = { .num = 0, .denom = 1 },
        reduced = { .num = 0, .denom = 1 };
    char c = '\0';

    while (1) 
    {
        while ( scanf("%d / %d", &input.num, &input.denom) != 2) {
            fprintf(stderr, "Input invalid. Please try again.\n");            

            while ( (c = getchar()) != '\n' && c != EOF) continue;
        }
        while ( (c = getchar()) != '\n' && c != EOF) continue;
    
        if (input.denom == 0) {
            fprintf(stderr, "Denominator cannot be equal to zero.\n");
            continue;
        }
        break;
    }
    FractionReduce(&input, &reduced);

    printf("In lowest terms: %d/%d\n", reduced.num, reduced.denom);

    getchar();
    return EXIT_SUCCESS;
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

int FractionReduce(
    const struct Fraction* fract,
    struct Fraction* OutResult) 
{
    if (!fract) return 1;

    int gcd = (int)Gcd(fract->num, fract->denom);

    OutResult->num = fract->num / gcd;
    OutResult->denom = fract->denom / gcd;

    return 0;
}
