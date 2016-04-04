#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <errno.h>

#include "Stack.h"
#include "Queue.h"

typedef double (*MathBinOpFuncPtr) (double, double);

double Add(double a, double b);

double Sub(double a, double b);

double Mul(double a, double b);

double Div(double a, double b);

double Mod(double a, double b);

int PolishExpressionParse(const char* exp, double* OutResult);

#define BUFFER_SIZE 256

// a driver program to test the Polish calculator

int main(void) {
    
    char buffer[BUFFER_SIZE] = { 0 };
    double result = 0.0;

    while (1) {
        printf(">>> ");
        fgets(buffer, BUFFER_SIZE, stdin);
        if (PolishExpressionParse(buffer, &result) != 0) {
            fprintf(stderr, "Input invalid.\n");
            continue;
        }
        printf("%lf\n", result);
    }

    getchar();
    return 0;
}

double Add(double a, double b) {
    return a + b;
}

double Sub(double a, double b) {
    return a - b;
}

double Mul(double a, double b) {
    return a * b;
}

double Div(double a, double b) {
    return a / b;
}

double Mod(double a, double b) {
    return a - (long long)a / (long long)b * b;
}

int PolishExpressionParse(const char* exp, double* OutResult) {    
    if (!exp) {
        errno = EINVAL;
        return EINVAL;
    }

    *OutResult = 0.0;

    static const char* supportedOperators[] = {
        "+", "-", "*", "/", "mod", NULL
    };
    
    static const MathBinOpFuncPtr supportedOperatorsFunc[] = {
        Add, Sub, Mul, Div, Mod
    };

    struct Queue operands = { 0 };
    QueueNew(&operands, sizeof(double));
    
    struct Stack tempOperands = { 0 };
    StackNew(&tempOperands, sizeof(double), NULL);

    struct Stack operators = { 0 };
    StackNew(&operators, sizeof(MathBinOpFuncPtr), NULL);
    
    size_t expLen = strlen(exp);
    size_t i = 0;
    size_t j = 0;

    do {
        if (i < expLen && (isdigit(exp[i]) || exp[i] == '.')) {
            j = i;
            while (j < expLen && (isdigit(exp[j]) || 
                                    exp[j] == '.' || 
                                    exp[j] == 'E' || 
                                    exp[j] == 'e')) 
            {
                ++j;
            }
            double value = 0.0;
            char* parseEnd = NULL;
            value = strtod(&exp[i], &parseEnd);
            if (parseEnd != &exp[j]) {
                errno = EINVAL;
                break;
            }
            QueueEnqueue(&operands, &value);

            i = j;

        } else if (i == expLen || exp[i] == ')') { 
            if (QueueGetCount(&operands) > 1) {

                MathBinOpFuncPtr opFuncPtr = NULL;
                StackPop(&operators, &opFuncPtr);
                
                double operand1 = 0.0;
                double operand2 = 0.0;
                QueueDequeue(&operands, &operand1);
                QueueDequeue(&operands, &operand2);
                    
                double result = (*opFuncPtr)(operand1, operand2);
                StackPush(&tempOperands, &result);    
                
                while (QueueGetCount(&operands) > 0) {
                    StackPop(&tempOperands, &operand1);
                    QueueDequeue(&operands, &operand2);
                    result = (*opFuncPtr)(operand1, operand2);
                    StackPush(&tempOperands, &result);    
                }
                StackPop(&tempOperands, &result);
                QueueEnqueue(&operands, &result);
                ++i;
            }
        } else if (i < expLen && !isspace(exp[i])) {
            const char** pOperator = &supportedOperators[0];
            j = 0;
            while (*pOperator != NULL) {
                size_t opLen = strlen(*pOperator);
                if (expLen - i >= opLen && strncmp(&exp[i], *pOperator, opLen) == 0) {
                
                    MathBinOpFuncPtr opFuncPtr = NULL;
                    opFuncPtr = supportedOperatorsFunc[j];
                    StackPush(&operators, &opFuncPtr);
                
                    i += opLen;
                
                    break;
                }
                ++j; ++pOperator;
            }
        }
        else { 
            ++i;
        }
    } while (i <= expLen && StackGetCount(&operators) > 0);

    double result = 0.0;

    if (StackGetCount(&operators) > 0) {
        errno = EINVAL;
    }
    if (QueueGetCount(&operands) > 0) {
        QueueDequeue(&operands, &result);
    } else {
        errno = EINVAL;
    }
    QueueDispose(&operands);
    StackDispose(&operators);
    StackDispose(&tempOperands);

    *OutResult = result;
    return 0;
}
