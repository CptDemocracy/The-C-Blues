#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>

/*K&R C (Dennis M. Ritchie & Brian W. Kernighan)
 Exercise 5-2. Write getfloat, the floating-point analog of getint. What type does getfloat
return as its function value?
*/

double ReadDouble(void) {
    char c = 0;
    int sign = 1;
    int expsign = 1;
    double mant = 0.0;
    double frac = 1.0;
    double exp  = 0.0;
    do {
        c = getchar();
    } while (isblank(c));
    if (c == '+' || c == '-') {
        if (c == '-') {
            sign = -1;
        }
        c = getchar();
    }
    while (isdigit(c)) {
        mant = mant * 10 + (c - '0');
        c = getchar();
    }
    if (c == '.') {
        c = getchar();
        if (isdigit(c)) {
            while (isdigit(c)) {
                mant = mant * 10 + (c - '0');
                frac *= 10.0;
                c = getchar();
            }
        } 
        if (c == 'E' || c == 'e') {
            c = getchar();
            if (c == '+' || c == '-') {
                if (c == '-') {
                    expsign = -1;
                }
                c = getchar();
            }
            if (isdigit(c)) {
                while (isdigit(c)) {
                    exp = exp * 10 + (c - '0');
                    c = getchar();
                }
            }
        }

        // return the character that should not
        // belong to us back to the stream
        ungetc(c, stdin);
    } 
    else if (c == 'E' || c == 'e') {
        c = getchar();
        if (c == '+' || c == '-') {
            if (c == '-') {
                expsign = -1;
            }
            c = getchar();
        }
        if (isdigit(c)) {
            while (isdigit(c)) {
                exp = exp * 10 + (c - '0');
                c = getchar();
            }
        } 

        // return the character that should not
        // belong to us back to the stream
        ungetc(c, stdin);
    }
    else {

        // return the character that should not
        // belong to us back to the stream
        ungetc(c, stdin);
    }
    return (double)sign * mant / frac * pow(10.0, exp * (double)expsign);
}

int main(void) {    

    char c = 0;
    double num = 0.0;
    printf("Please enter a floating-point number: \n");
    while (1)
    {
        printf(">>> ");
        num = ReadDouble();

        // flush redundant input
        while (c != '\n') {
            c = getchar();
        }
        c = 0;

        printf("%.14g\n", num);
    }

    getchar();
    return 0;
}
