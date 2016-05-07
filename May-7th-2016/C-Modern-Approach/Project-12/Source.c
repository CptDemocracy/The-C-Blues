/*
K.N.King "C Programming. A Modern Approach."
Programming project 12 p.157

Write a program that evaluates an expression:

Enter an expression: 1+2.5*3
Value of expression: 10.5

The operands in the expression are floating-
point numbers; the operators are +, -, * and
/. The expression is evaluated from left to
right (no operator takes precedence over any
other operator).

*/

#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <errno.h>

#include "Queue.h"

errno_t Add(double a, double b, double* OutResult);
errno_t Sub(double a, double b, double* OutResult);
errno_t Mul(double a, double b, double* OutResult);
errno_t Div(double a, double b, double* OutResult);

typedef errno_t (*MathExpressionFuncPtr) (double, double, double*);

int DiscardLineOfInput(FILE* stream);

int main(void) 
{
    const MathExpressionFuncPtr OPERATOR_LOOKUP_TABLE[UCHAR_MAX] = {
        ['+'] = &Add,
        ['-'] = &Sub,
        ['*'] = &Mul,
        ['/'] = &Div
    };
    
    struct Queue operandQueueDouble = { 0 };
    if ( QueueNew(&operandQueueDouble, sizeof(double)) != 0) {
        return EXIT_FAILURE;
    }
    struct Queue operatorQueueMathExpressionFuncPtr = { 0 };
    if ( QueueNew(&operatorQueueMathExpressionFuncPtr, sizeof(MathExpressionFuncPtr)) != 0) {
        return EXIT_FAILURE;
    }

    double operand  = 0.0;
    double operandA = 0.0;
    double operandB = 0.0;
    double result = 0.0;

    int scanfState = 0;
    errno_t err = 0;

    char optor = '\0';
    char c = '\0';
    
    MathExpressionFuncPtr operatorFuncPtr = NULL;

    printf("Enter an expression: ");

    while (1)
    {
        scanfState = scanf(" %lf", &operand);
        if (scanfState != 1) {
            fprintf(stderr, "Error parsing an expression.\n");
            
            DiscardLineOfInput(stdin);
            break;
        }

        QueueEnqueue(&operandQueueDouble, &operand);
        
        if (QueueGetCount(&operandQueueDouble) > 1 
            && QueueGetCount(&operatorQueueMathExpressionFuncPtr) > 0) 
        {
            QueueDequeue(&operandQueueDouble, &operandA);            
            QueueDequeue(&operandQueueDouble, &operandB);                        
            QueueDequeue(&operatorQueueMathExpressionFuncPtr, &operatorFuncPtr);

            result = 0.0;
            err = 0;
            err = (*operatorFuncPtr)(operandA, operandB, &result);
            if (err) {
                fprintf(stderr, "Error parsing an expression.\n");

                DiscardLineOfInput(stdin);
                break;
            }
            QueueEnqueue(&operandQueueDouble, &result);
        }

        // check for the new line char, if it's there,
        // user has already entered the line of input.
        // if so, break out of the loop
        c = getchar();

        if (c == '\n') {
            break;
        } else {
            // don't forget to put it back if it's not
            // a new line character
            ungetc(c, stdin);
        }
        scanfState = scanf(" %c", &optor);
        if (scanfState != 1) {
            fprintf(stderr, "Error parsing an expression.\n");
            
            DiscardLineOfInput(stdin);
            break;
        }

        operatorFuncPtr = OPERATOR_LOOKUP_TABLE[optor];
        if (operatorFuncPtr) {
            QueueEnqueue(&operatorQueueMathExpressionFuncPtr, &operatorFuncPtr);
        } else {
            fprintf(stderr, "Operator invalid.\n");
            break;
        }
    }
    
    printf("Value of expression: %g\n", result);

    QueueDispose(&operandQueueDouble);
    QueueDispose(&operatorQueueMathExpressionFuncPtr);

    getchar();
    return EXIT_SUCCESS;
}

errno_t Add(double a, double b, double* OutResult) {
    if (!OutResult) {
        return 1;
    }
    *OutResult = a + b;
    return 0;
}

errno_t Sub(double a, double b, double* OutResult) {
    if (!OutResult) {
        return 1;
    }
    *OutResult = a - b;
    return 0;
}

errno_t Mul(double a, double b, double* OutResult) {
    if (!OutResult) {
        return 1;
    }
    *OutResult = a * b;
    return 0;
}

errno_t Div(double a, double b, double* OutResult) {
    if (!OutResult) {
        return 1;
    }
    if (b == 0.0) {
        return 2;
    }
    *OutResult = a / b;
    return 0;
}

int DiscardLineOfInput(FILE* stream) {
    if (!stream) {
        return 1;
    }
    char c = '\0';
    while ((c = fgetc(stream)) != '\n') {
        if (c == EOF) {
            return EOF;
        }
    }
    return 0;
}
