/*
K.N.King "C Programming. A Modern Approach."
Programming project 6 p.50

Modify the addfrac.c program of Section 3.2 so that the user
enters both fractions at the same time, separated by a plus sign:
"Enter two fractions separated by a plus sign: 5/6+3/4
The sum is 38/24
"

*/

#include <stdlib.h>
#include <stdio.h>

#define INPUT_INVALID_MSG       "Input invalid. Please try again."
#define INTERNAL_ERROR_MSG      "An internal error has occured trying to parse the operator."

struct Fraction
{
    int num;
    int denom;
};

struct Fraction FractionAdd(const struct Fraction *fr1, const struct Fraction *fr2);

struct Fraction FractionSub(const struct Fraction *fr1, const struct Fraction *fr2);

struct Fraction FractionMul(const struct Fraction *fr1, const struct Fraction *fr2);

struct Fraction FractionDiv(const struct Fraction *fr1, const struct Fraction *fr2);

struct Fraction FractionReduce(const struct Fraction *fr);

int gcd(int n, int m);

int main(void) {

    struct Fraction 
        frac1  = { .num = 0, .denom = 1 },
        frac2  = { .num = 0, .denom = 1 },
        result = { .num = 0, .denom = 1 };
    char op = '\0';
    int scanfState = 0;

    while (1)
    {
        scanfState = 
            scanf("%d/%d %c %d/%d", 
            &frac1.num, 
            &frac1.denom, 
            &op, 
            &frac2.num, 
            &frac2.denom);
        if (scanfState < 5) {
            // input invalid, inform the user,
            // discard invalid input from the
            // stream and request input again
            puts(INPUT_INVALID_MSG);

            char c = '\0';
            while ((c = getchar()) != '\n' && c != EOF) {
                continue;
            }
            continue;
        }
        // consume trailing new line character 
        // left by the scanf function
        getchar();
        break;
    }

    switch (op) 
    {
        case '+':
            result = FractionAdd(&frac1, &frac2);
            break;
        case '-':
            result = FractionSub(&frac1, &frac2);
            break;
        case '*':
            result = FractionMul(&frac1, &frac2);
            break;
        case '/':
            result = FractionDiv(&frac1, &frac2);
            break;
        default:
            puts(INTERNAL_ERROR_MSG);
            return EXIT_FAILURE;
            break;
    }
    result = FractionReduce(&result);
    printf("%d/%d\n", result.num, result.denom);
    getchar();
    return EXIT_SUCCESS;
}

struct Fraction FractionAdd(const struct Fraction *fr1, const struct Fraction *fr2) {
    struct Fraction result = { .num = 0, .denom = 1 };
    if (!fr1 || !fr2 || fr1->denom == 0 || fr2->denom == 0) {
        return result;
    }
    result.num = fr1->num * fr2->denom + fr1->denom * fr2->num;
    result.denom = fr1->denom * fr2->denom;
    return result;
}

struct Fraction FractionSub(const struct Fraction *fr1, const struct Fraction *fr2) {
    struct Fraction result = { .num = 0, .denom = 1 };
    if (!fr1 || !fr2 || fr1->denom == 0 || fr2->denom == 0) {
        return result;
    }
    result.num = fr1->num * fr2->denom - fr1->denom * fr2->num;
    result.denom = fr1->denom * fr2->denom;
    return result;
}

struct Fraction FractionMul(const struct Fraction *fr1, const struct Fraction *fr2) {
    struct Fraction result = { .num = 0, .denom = 1 };
    if (!fr1 || !fr2 || fr1->denom == 0 || fr2->denom == 0) {
        return result;
    }
    result.num = fr1->num * fr2->num;
    result.denom = fr1->denom * fr2->denom;
    return result;
}

struct Fraction FractionDiv(const struct Fraction *fr1, const struct Fraction *fr2) {
    struct Fraction result = { .num = 0, .denom = 1 };
    if (!fr1 || !fr2 || fr1->denom == 0 || fr2->denom == 0) {
        return result;
    }
    result.num = fr1->num * fr2->denom;
    result.denom = fr1->denom * fr2->num;
    return result;
}

struct Fraction FractionReduce(const struct Fraction *fr) {
    struct Fraction result = { .num = 0, .denom = 1 };
    if (!fr) {
        return result;
    }
    int gcdiv = gcd(fr->num, fr->denom);
    result.num = fr->num / gcdiv;
    result.denom = fr->denom / gcdiv;
    return result;
}

int gcd(int n, int m) {
    int temp = 0;
    while (m > 0) {
        temp = m;
        m = n % m;
        n = temp;
    }
    return n;
}
