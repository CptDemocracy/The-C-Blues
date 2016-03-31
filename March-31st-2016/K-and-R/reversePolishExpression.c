#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <errno.h>
#include <math.h>

#include "Stack.h"

/*K&R C (Dennis M. Ritchie & Brian W. Kernighan)
 Exercise 5-10. Write the program expr, which evaluates a reverse Polish expression 
 from the command line, where each operator or operand is a separate argument. For 
 example:
	expr 2 3 4 + *
 evaluates 2 * (3+4).
*/

int DoubleTryParse(const char* s, double* OutResult);

double Expr(int argc, const char* argv[]);

double(*OperatorTryParse(const char* s))(double, double);

double Add(double a, double b);

double Mul(double a, double b);

double Div(double a, double b);

double Sub(double a, double b);

int main(int argc, const char* argv[]) {    
	
	int argcount = argc - 1;
	const char** args = &argv[1];

	double result = Expr(argcount, args);
	printf("%lf\n", result);

    getchar();
    return 0;
}

double Expr(int argcount, const char* args[]) {

	double result = 0.0;

	struct Stack stack = { 0 };
	StackNew(&stack, sizeof(double), NULL);

	double operand = 0.0;
	double (*operation)(double, double) = NULL;
	for (int i = 0; i < argcount; ++i) {
		if (DoubleTryParse(args[i], &operand)) {
			StackPush(&stack, &operand);
		}
		else if (operation = OperatorTryParse(args[i])) {
			if (StackGetCount(&stack) > 1) {
				StackPop(&stack, &result);
				StackPop(&stack, &operand);
				result = (*operation)(operand, result);
				StackPush(&stack, &result);
			}
		} 
		else {
			return 0.0;
		}
	}

	StackDispose(&stack);
	return result;
}

double Add(double a, double b) {
	return a + b;
}

double Mul(double a, double b) {
	return a * b;
}

double Div(double a, double b) {
	return a / b;
}

double Sub(double a, double b) {
	return a - b;
}

double(*OperatorTryParse(const char* s))(double, double) {
	
	if (!s) return NULL;

	while (isspace(*s)) ++s;

	switch (*s) {
		case '+':
			return &Add;
			break;
		case '-':
			return &Sub;
			break;
		case '/':
			return &Div;
			break;
		case '*':
			return &Mul;
			break;
		default:
			break;
	}
	return NULL;
}

int DoubleTryParse(const char* s, double* OutResult) {
    
	if (!OutResult) return 0;

    if (!s) {
		*OutResult = 0.0;
		return 0;
	}
    
    while (isspace(*s)) ++s;

    int sign = 1;
    double frac = 1.0;
    double result = 0.0;

    if (*s == '-') {
        sign = -1;
        ++s;
    }
    else if (*s == '+') {
        ++s;
    }
	if (!isdigit(*s)) {
		return 0;
	}
    while (isdigit(*s)) {
        result = result * 10.0 + (*s - '0');
        ++s;
    }
    if (*s == '.') {
        ++s;
        while (isdigit(*s)) {
            result = result * 10.0 + (double)(*s - '0');
            frac *= 10;
            ++s;
        }

        if (*s == 'E' || *s == 'e') {
            ++s;
        
            double exp = 0.0;
            int fracsign = 1;

            if (*s == '-') {
                fracsign = -1;
                ++s;
            }
            else if (*s == '+') {
                fracsign = 1;
                ++s;
            }
            
            while (isdigit(*s)) {
                exp = exp * 10.0 + (*s - '0');
                ++s;
            }
            exp *= fracsign;
        
			*OutResult = sign * result / frac * pow(10.0, exp);
            return 1;
        }

		*OutResult = sign * result / frac;
        return 1;
    }
    else if (*s == 'E' || *s == 'e') {
        ++s;
        
        double exp = 0.0;
        int fracsign = 1;

        if (*s == '-') {
            fracsign = -1;
        }
        else if (*s == '+') {
            fracsign = 1;
        }

        ++s;

        while (isdigit(*s)) {
            exp = exp * 10.0 + (*s - '0');
            ++s;
        }
        exp *= fracsign;
        
		*OutResult = sign * result * pow(10.0, exp);
        return 1;
    }
    
	*OutResult = result;
    return 1;
}
