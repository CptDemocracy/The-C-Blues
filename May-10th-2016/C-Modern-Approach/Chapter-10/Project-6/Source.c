/*
K.N.King "C Programming. A Modern Approach."
Programming project 6 p.239

Some calculators (notably those from Hewlett-Packard) use a system 
of writing mathematical expressions known as Reverse Polish Notation (RPN). 
In this notation, operators are placed <i>after</i> their operands instead 
of <i>between</i> their operands. For example, "1 + 2 "would be written 
"1 2 +" in RPN, and "1 + 2 * 3" would be written "1 2 3 * +". RPN expressions 
can easily be evaluated using a stack. The algorithm involves reading the 
operators and operands in an expression from left to right, performing the 
following actions:

    When an operand is encountered, push it onto the stack.
    When an operator is encountered, pop its operands from the stack,
        perform the operation on those operands, and then push the result
        onto the stack.
    
Write a program that evaluates RPN expressions. The operands will be single-
digit integers. The operators are +, -, *, /, and =. The = operator causes
the top stack item to be displayed; afterwards, the stack is cleared and 
the user is prompted to enter another expression. The process continues
until the user enters a character that is not an operator or operand:
"Enter an RPN expression: 1 2 3 * + =
Value of expression: 7
Enter an RPN expression: 5 8 * 4 9 - / =
Value of expression: -8
Enter an RPN expression: q
"

If the stack overflows, the program will display the message "Expression 
is too complex" and terminate. If the stack underflows (because of an 
expression such as "1 2 + +"), the program will display the message 
"Not enough operands in expression" and terminate.

*/

/*
NOTE: this implementation does not require users to pass the '=' operator
to have their value output in the screen. In fact, this implementation 
dropped support of the '=' operator.
*/

#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

#include "Stack.h"
#include "Queue.h"

#define STATE_SUCCESS            0
#define STATE_OVERFLOW            1
#define STATE_UNDERFLOW            2
#define STATE_INVALID_FORMAT    3
#define STATE_OUT_OF_MEMORY        4
#define STATE_NOT_SUPPORTED        5
#define STATE_INVALID_OPERAND    6
#define STATE_INVALID_ARGUMENT    7
#define STATE_QUIT                8

int RPNEvaluate(const char* exp, double* OutResult);

typedef int (*MathExpressionFuncPtr)(const double* args, int argc, double* OutResult);

struct MathOperator 
{
    char optor;
    int argCount;
    MathExpressionFuncPtr func;
};

int Div(const double* args, int argc, double* OutResult);
int Mul(const double* args, int argc, double* OutResult);
int Add(const double* args, int argc, double* OutResult);
int Sub(const double* args, int argc, double* OutResult);
int Quit(const double* args, int argc, double* OutResult);

int main(void)
{
    char c = '\0';
    double result = 0.0;
    int state = 0;

    char* inputBuffer = NULL;
    size_t inputCount = 0;

    struct Queue inputCharQueue = { 0 };
    if ( QueueNew(&inputCharQueue, sizeof(char)) != 0) {
        return EXIT_FAILURE;
    }

    while (state != STATE_QUIT)
    {    
        printf("Please enter an RPN expression: ");

        while ((c = getchar()) != '\n' && c != EOF) {
            (void) QueueEnqueue(&inputCharQueue, &c);
        }
        inputCount = QueueGetCount(&inputCharQueue);    

        char* newBuffer = (char*)realloc(inputBuffer, (inputCount + 1) * sizeof(char));
        if (!newBuffer) {
            state = STATE_OUT_OF_MEMORY;
            break;
        }
        inputBuffer = newBuffer;

        for (size_t i = 0u; i < inputCount; ++i) {
            (void) QueueDequeue(&inputCharQueue, &inputBuffer[i]);
        }
        inputBuffer[inputCount] = '\0';

        state = RPNEvaluate(inputBuffer, &result);
        if (state == STATE_SUCCESS) {
            printf("Value of expression: %g\n", result);
        }
        else if (state == STATE_OVERFLOW) {
            fprintf(stderr, "Error: too many operands in the expression.\n");
        }
        else if (state == STATE_UNDERFLOW) {
            fprintf(stderr, "Error: not enough operands in the expression.\n");
        }
        else if (state == STATE_INVALID_FORMAT) {
            fprintf(stderr, "Error: expression is in invalid format.\n");
        }
        else if (state == STATE_OUT_OF_MEMORY) {
            fprintf(stderr, "Error: computer out of memory.\n");
        }
        else if (state == STATE_NOT_SUPPORTED) {
            fprintf(stderr, "Error: operator not supported.\n");
        }
        else if (state == STATE_INVALID_OPERAND) {
            fprintf(stderr, "Error: invalid operand.\n");
        }
        else if (state == STATE_QUIT) {
            printf("Thank you for using our application!\n");
        }
        else {
            fprintf(stderr, "Internal error has occured. Please contact your software vendor.\n");
        }
    }

    free(inputBuffer);
    QueueDispose(&inputCharQueue);

    getchar();
    return EXIT_SUCCESS;
}


int RPNEvaluate(const char* exp, double* OutResult) {
    if (!exp) {
        return STATE_INVALID_FORMAT;
    }
    if (!OutResult) {
        return STATE_INVALID_FORMAT;
    }

    int state = 0;

    const static size_t MAX_ARG_COUNT = 2;
    const static struct MathOperator SUPPORTED_OPERATORS[UCHAR_MAX] = {
        ['/'] = { .optor = '/', .argCount = 2, .func = &Div  },
        ['*'] = { .optor = '*', .argCount = 2, .func = &Mul  },
        ['+'] = { .optor = '+', .argCount = 2, .func = &Add  },
        ['-'] = { .optor = '-', .argCount = 2, .func = &Sub  },
        ['q'] = { .optor = 'q', .argCount = 0, .func = &Quit },
        ['Q'] = { .optor = 'Q', .argCount = 0, .func = &Quit },
    };
    const static size_t SUPPORTED_OPERATOR_COUNT 
        = sizeof(SUPPORTED_OPERATORS) / sizeof(SUPPORTED_OPERATORS[0]);
    
    double* argBuffer = (double*)calloc(MAX_ARG_COUNT, sizeof(double));
    if (!argBuffer) {
        return STATE_OUT_OF_MEMORY;
    }

    const struct MathOperator* mathOpPtr = NULL;

    struct Stack operandDoubleStack = { 0 };
    state = StackNew(&operandDoubleStack, sizeof(double), NULL);
    if (state) {
        return state;
    }
    
    char optor = '\0';
    char* pchar = NULL;
    double operand = 0.0;
    double result = 0.0;    

    while (1) {
        operand = strtod(exp, &pchar);
        if (pchar != exp) {
            (void) StackPush(&operandDoubleStack, &operand);
            exp = pchar;
        } else {
            while (isspace(*exp)) ++exp;
            optor = *exp;
            
            if (optor == '\0') {
                break;
            } else {
                ++exp;
            }

            mathOpPtr = &SUPPORTED_OPERATORS[optor];

            if (mathOpPtr) {
                if (mathOpPtr->argCount <= (int)StackGetCount(&operandDoubleStack)) {
                    int i = 0;
                    for (int i = 0; i < mathOpPtr->argCount; ++i) {
                        (void) StackPop(&operandDoubleStack, &argBuffer[MAX_ARG_COUNT - i % MAX_ARG_COUNT - 1]);
                    }
                    state = mathOpPtr->func(argBuffer, mathOpPtr->argCount, &result);
                    if (state) {
                        break;
                    }
                    StackPush(&operandDoubleStack, &result);
                } else {
                    state = STATE_UNDERFLOW;
                    break;
                }
            } else {
                state = STATE_NOT_SUPPORTED;
                break;
            }
        }
    }

    if (state == STATE_SUCCESS) {
        if ((int)StackGetCount(&operandDoubleStack) == 1) {
            memcpy(OutResult, &result, sizeof(double));
        } else {
            state = STATE_OVERFLOW;
        }
    }    

    free(argBuffer);
    StackDispose(&operandDoubleStack);

    return state;
}

int Div(const double* args, int argc, double* OutResult) {
    if (!args) {
        return STATE_INVALID_ARGUMENT;
    }
    if (argc != 2) {
        return STATE_INVALID_ARGUMENT;
    }
    if (!OutResult) {
        return STATE_INVALID_ARGUMENT;
    }

    double result = 0.0;
    double a = 0.0;
    double b = 0.0;

    a = args[0];
    b = args[1];

    if (b == 0.0) {
        return STATE_INVALID_OPERAND;
    }

    result = a / b;
    memcpy(OutResult, &result, sizeof(double));
    return STATE_SUCCESS;
}

int Mul(const double* args, int argc, double* OutResult) {
    if (!args) {
        return STATE_INVALID_ARGUMENT;
    }    
    if (argc != 2) {
        return STATE_INVALID_ARGUMENT;
    }
    if (!OutResult) {
        return STATE_INVALID_ARGUMENT;
    }

    double result = 0.0;
    double a = 0.0;
    double b = 0.0;

    a = args[0];
    b = args[1];

    result = a * b;
    memcpy(OutResult, &result, sizeof(double));
    return STATE_SUCCESS;
}

int Add(const double* args, int argc, double* OutResult) {
    if (!args) {
        return STATE_INVALID_ARGUMENT;
    }    
    if (argc != 2) {
        return STATE_INVALID_ARGUMENT;
    }
    if (!OutResult) {
        return STATE_INVALID_ARGUMENT;
    }
    
    double result = 0.0;
    double a = 0.0;
    double b = 0.0;

    a = args[0];
    b = args[1];

    result = a + b;
    memcpy(OutResult, &result, sizeof(double));
    return STATE_SUCCESS;
}

int Sub(const double* args, int argc, double* OutResult) {
    if (!args) {
        return STATE_INVALID_ARGUMENT;
    }    
    if (argc != 2) {
        return STATE_INVALID_ARGUMENT;
    }
    if (!OutResult) {
        return STATE_INVALID_ARGUMENT;
    }
    
    double result = 0.0;
    double a = 0.0;
    double b = 0.0;

    a = args[0];
    b = args[1];

    result = a - b;
    memcpy(OutResult, &result, sizeof(double));
    return STATE_SUCCESS;
}

int Quit(const double* args, int argc, double* OutResult) {
    return STATE_QUIT;
}
