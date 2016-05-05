/*
K.N.King "C Programming. A Modern Approach."
Programming project 5 p.96

In one state, single residents are subject to
the following income tax:

Income:            Amount of tax:
Not over $750    1% of income
$750-$2,250      $7.50      plus 2% of the amount
$2,250-$3,750    $37.50     plus 3% of the amount
$3,750-$5,250    $82.50     plus 4% of the amount
$5,250-$7,000    $142.50    plus 5% of the amount
Over $7,000      $230.00    plus 6% of the amount

Write a program that asks the user to enter 
the amount of taxable income, then displays
the tax due.
*/

#include <stdlib.h>
#include <stdio.h>

double CalculateTaxDue(double taxableIncome);

int main(void) 
{
    double income = 0.0;
    double taxdue = 0.0;
    int isInputValid = 0;

    while (!isInputValid)
    {
        printf("Please enter the amount of taxable income: ");

        if ( scanf("%lf", &income) == 1) {
            if (income < 0.0) {
                puts("Income cannot be negative. Please try again.");
            } else {
                isInputValid = 1;
            }
        } else {
            puts("Invalid input. Please try again.");
        }        
        // discard trailing input left by scanf
        char c = '\0';
        while ( (c = getchar()) != '\n' && c != EOF) continue;
    }
    taxdue = CalculateTaxDue(income);
    printf("Income: $%.2lf\n", income);
    printf("Tax due: $%.2lf\n", taxdue);

    getchar();
    return EXIT_SUCCESS;
}

/*
The tax is calculated based on the following table:
    Income:            Amount of tax:
    Not over $750    1% of income
    $750-$2,250      $7.50      plus 2% of the amount
    $2,250-$3,750    $37.50     plus 3% of the amount
    $3,750-$5,250    $82.50     plus 4% of the amount
    $5,250-$7,000    $142.50    plus 5% of the amount
    Over $7,000      $230.00    plus 6% of the amount
*/
double CalculateTaxDue(double taxableIncome) {
    if (taxableIncome < 0.0) {
        return 0.0;
    }
    double taxdue = 0.0;

    if (taxableIncome < 750.0) {
        taxdue = taxableIncome * 0.01;
    }
    else if (taxableIncome < 2250.0) {
        taxdue = 7.5 + taxableIncome * 0.02;
    }
    else if (taxableIncome < 3750.0) {
        taxdue = 37.5 + taxableIncome * 0.03;
    }
    else if (taxableIncome < 5250.0) {
        taxdue = 82.5 + taxableIncome * 0.04;
    }
    else if (taxableIncome < 7000.0) {
        taxdue = 142.5 + taxableIncome * 0.05;
    }
    else {
        taxdue = 230.0 + taxableIncome * 0.06;
    }
    return taxdue;
}
