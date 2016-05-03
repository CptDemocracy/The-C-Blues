/*
K.N.King "C Programming. A Modern Approach."

Programming project 2 p.50

"Write a program that formats product information entered by
the user. A session with the program should look like this:

Enter item number: 583
Enter unit price: 13.5
Enter purchase date (mm/dd/yyyy): 10/24/2010

Item    Unit        Purchase
        Price        Date
583        $    13.50    10/24/2010

The item number and date should be left justified;
The unit price should be right justified;
Allow dollar amounts up to $9999.99.
"

*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

struct Product
{
    int id;
    double price;
    struct tm purchaseDate;
};

int ReadInt(int *OutResult, void (*OnInvalidInput)(void));

int ReadDouble(double *OutResult, void (*OnInvalidInput)(void));

int ReadDate(struct tm *OutResult, void (*OnInvalidInput)(void));

void OnInvalidInputHandler(void);

int main(void)
{
    // initialize to zeros
    struct Product prod = { 0 };

    printf("Enter item number: ");
    ReadInt(&prod.id, &OnInvalidInputHandler);

    printf("Enter unit price: ");
    ReadDouble(&prod.price, &OnInvalidInputHandler);

    printf("Enter purchase date (mm/dd/yyyy): ");
    ReadDate(&prod.purchaseDate, &OnInvalidInputHandler);

    printf("%s\t%s\t%s\n", "Item", "Unit Price", "Purchase Date");
    printf("%d\t$%.2Lf\t\t%02d/%02d/%d\n",
        prod.id,
        prod.price,
        prod.purchaseDate.tm_mon,
        prod.purchaseDate.tm_mday,
        prod.purchaseDate.tm_year);
    getchar();

    return EXIT_SUCCESS;
}

int ReadInt(int *OutResult, void (*OnInvalidInput)(void)) {
    if (!OutResult) {
        return 1;
    }
    // keep prompting the user
    // until we get valid input
    while (scanf("%d", OutResult) < 1) {
        // input invalid, discard invalid input
        char c = '\0';
        while ((c = getchar()) != '\n' && c != EOF) {
            continue;
        }
        // call the handler 
        // if such was provided by the caller
        if (OnInvalidInput) (*OnInvalidInput)();
    }
    // consume trailing new line character
    getchar();
    return 0;
}

int ReadDouble(double *OutResult, void (*OnInvalidInput)(void)) {
    if (!OutResult) {
        return 1;
    }
    // keep prompting the user
    // until we get valid input
    while (scanf("%Lf", OutResult) < 1) {
        // input invalid, discard invalid input
        char c = '\0';
        while ((c = getchar()) != '\n' && c != EOF) {
            continue;
        }
        // call the handler 
        // if such was provided by the caller
        if (OnInvalidInput) (*OnInvalidInput)();
    }
    // consume trailing new line character
    getchar();
    return 0;
}

int ReadDate(struct tm *OutResult, void (*OnInvalidInput)(void)) {
    if (!OutResult) {
        return 1;
    }
    // format mm/dd/yyyy

    // keep prompting the user
    // until we get valid input
    while (scanf("%d/%d/%d", &OutResult->tm_mday, &OutResult->tm_mon, &OutResult->tm_year) <3) {
        // input invalid, discard invalid input
        char c = '\0';
        while ((c = getchar()) != '\n' && c != EOF) {
            continue;
        }
        // call the handler 
        // if such was provided by the caller
        if (OnInvalidInput) (*OnInvalidInput)();
    }
    // consume trailing new line character
    getchar();
    return 0;
}

void OnInvalidInputHandler(void) {
    puts("Input invalid. Please try again.");
}
