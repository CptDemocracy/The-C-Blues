/*
K.N.King "C Programming. A Modern Approach."
Programming project 7 p.217

The power function of Section 9.6 can be made faster by having it 
calculate x^n in a different way. We first notice that if n is 
a power of 2, then x^n can be computed by squaring. For example,
x^4 is the square of x^2, so x^4 can be computed using only two 
multiplications in lieu of three.

As it happens, this technique can be used even when n is not 
a power of 2.

If n is even, we use the formula x^n = (x^(n/2))^2.
If n is odd, then x^n = x * x^(n - 1).

Write a recursive function that computes x^n. 

The recursion ends when n = 0, in which case the function 
returns 1.)

To test your function, write a program that asks the user to 
enter values for x and n, calls power to compute x^n, and then 
displays the value returned by the function.

*/

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <math.h>

long long Power(long long, long long);

long long PowerHelper(long long, long long);

int main(void)
{
    long long x = 0LL;
    long long pw = 0LL;
    long long result = 0LL;

    char c = '\0';
        
    printf("Please enter an integer: ");

    while (scanf("%lld", &x) != 1) {
        fprintf(stderr, "Input invalid. Please try again.\n");

        while ((c = getchar()) != '\n' && c != EOF) continue;
    }
    while ((c = getchar()) != '\n' && c != EOF) continue;        
    
    printf("Please enter a positive power: ");
        
    while (1)
    {
        while (scanf("%lld", &pw) != 1) {
            fprintf(stderr, "Input invalid. Please try again.\n");

            while ((c = getchar()) != '\n' && c != EOF) continue;
        }
        while ((c = getchar()) != '\n' && c != EOF) continue;

        if (pw < 0LL) {
            fprintf(stderr, "Negative powers not supported. "
                            "Please enter a positive value for power\n");
        } else {
            break;
        }
    }

    result = Power(x, pw);
    printf("%lld\n", result);

    getchar();
    return EXIT_SUCCESS;
}

long long Power(long long x, long long n) {
    if (n < 0.0) {
        if (n == LLONG_MIN) {
            errno = EDOM;
            return 0LL;
        }
        return 1LL / PowerHelper(x, -n);
    }
    return PowerHelper(x, n);
}

long long PowerHelper(long long x, long long n) {
    if (n == 0LL) {
        return 1LL;
    }
    if (n % 2LL == 0LL) {
        x = Power(x, n / 2LL);
        return x * x;
    }
    return x * Power(x, n - 1LL);
}
