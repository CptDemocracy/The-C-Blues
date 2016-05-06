/*
K.N.King "C Programming. A Modern Approach."
Programming project 4 p.121

Add a loop to the broker.c program of Section 5.2 so that
the user can enter more than one trade and the program will
calculate the commission on each. The program should terminate
when the user enters 0 as the trade value:

"Enter value of trade: 30000
Commission: $166.00

Enter value of trade: 20000
Commission: $144.00

Enter value of trade: 0

*/

#include <stdlib.h>
#include <float.h>
#include <stdio.h>
#include <math.h>

int main(void) 
{
    const double EPSILON = 1.0 * pow(10.0, (DBL_DIG - 1) * -1.0);

    double commission = 0.0;
    double value = 0.0;

    char c = '\0';
    while (1)
    {
        printf("Enter value of trade (0 to quit): ");

        while ( scanf("%lf", &value) != 1) {
            fprintf(stderr, "Input invalid. Please try again.\n");

            while ( (c = getchar()) != '\n' && c != EOF) continue;
            continue;
        }
        while ( (c = getchar()) != '\n' && c != EOF) continue;

        if (value <= EPSILON) {
            break;
        }
        else if (value < 0.0) {
            fprintf(stderr, "The value of trade cannot be negative. Please try again.\n");
            continue;
        }
        else {
            if (value < 2500.00f) {
                commission = 30.00f + .017f * value;
            } 
            else if (value < 6250.00f) {
                commission = 56.00f + .0066f * value;
            }
            else if (value < 20000.00f) {
                commission = 76.00f + .0034f * value;
            }
            else if (value < 50000.00f) {
                commission = 155.00f + .0011f * value;
            }
            else {
                commission = 255.00f + .0009f * value;
            }
            if (commission < 39.00f) commission = 39.00f;

            printf("Commission: $%.2lf\n", commission);
        }
    }
    puts("Thank you for using our application!");
    getchar();
    return EXIT_SUCCESS;
}
