/*
K.N.King "C Programming. A Modern Approach."
Programming project 1 p.346



*/

#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

int main(const int argc, const char* argv[]) {

    int x = 0;
    int y = 0;
    int result = 0;

    char c = '\0';
    char op[2] = { 0 };

    int isValid = 1;

    if (scanf("%d", &x) == 1) 
    {
        while (1) 
        {
            if (scanf(" %1[+-] %d", &op, &y) == 2) 
            {
                switch (op[0]) 
                {
                    case '+':
                        result = x + y;
                        break;
                    case '-':
                        result = x - y;
                        break;
                    case '/':
                        if (y == 0) {
                            isValid = 0;
                            break;
                        }
                        result = x / y;
                        break;
                    case '*':
                        result = x * y;
                        break;
                    default:
                        break;
                }
                if (!isValid) break;

                x = result;

                while ((c = getchar()) != EOF && isspace(c) && c != '\n') continue;

                if (c == '\n') {
                    (void) printf("%d\n", result);
                    break;
                } else {
                    (void) ungetc(c, stdin);
                }
            } else {
                isValid = 0;
                break;
            }
        }
    } else {
        isValid = 0;
    }
    if (!isValid) {
        while ((c = getchar()) != '\n' && c != EOF) continue;

        (void) fprintf(stderr, "Error. Unsupported operation.\n");
    }

    (void) getchar();
    return EXIT_SUCCESS;
}
