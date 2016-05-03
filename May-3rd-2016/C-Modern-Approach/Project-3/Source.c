/*
K.N.King "C Programming. A Modern Approach."
Programming project 3 p.50
"Books are identified by an International Standard Book Number
(ISBN). ISBNs assigned after January 1, 2007 contain 13 digits,
arranged in five groups, such as 978-0-393-97950-3 (Older ISBNs
use 10 digits.) The first group (the GSI prefix) is currently
either 978 or 979. The group identified specifies the language
or country of origin (for example, 0 and 1 are used in English-
speaking countries). The publisher code identifies the publisher
(393 is the code for W.W.Norton). The item number is assigned by
the publisher to identify a specific book (97950 is the code for
this book). An ISBN ends with a check digit that's used to verify
the accuracy of the preceding digits. Write a program that breaks
down an ISBN entered by the user:
Enter ISBN: 978-0-393-97950-3
GS1 prefix: 978
Group identifier: 0
Publisher code: 393
Item number: 97950
Check digit: 3
"
Note: The number of digits in each group may vary; you can't assume 
that groups have the lengths shown in this example. Test your program 
with actual ISBN values (usually found on the back cover of a book and 
on the copyright page).
*/

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

#define BUFFER_SIZE            256
#define INPUT_INVALID_MSG    "Input invalid. Please try again."

struct ISBN 
{
    // extra byte for every string 
    // to store the null terminator
    char gs1prefix[4];
    char groupId[2];
    char publisherCode[4];
    char itemNo[6];
    char checkDigit[2];
};

int IsNumericLiteral(const char* s);

int main(void)
{
    const char *FORMAT_STRING = "%%%ds-%%%ds-%%%ds-%%%ds-%%%ds";
    char buffer[BUFFER_SIZE] = { 0 };
    struct ISBN isbnCode = { 0 };
    int scanfState = 0;
    int isInputValid = 0;

    const char *numericLiteralsToValidate[] = { 
        isbnCode.gs1prefix, isbnCode.groupId, 
        isbnCode.publisherCode, isbnCode.itemNo, 
        isbnCode.checkDigit, 
        NULL // null-terminate the array
    };

    // set up a format string in the buffer
    // we need to specify widths and provide
    // an extra byte for the null terminating
    // character.
    sprintf_s(buffer, BUFFER_SIZE, FORMAT_STRING,
        ( sizeof(isbnCode.gs1prefix) - 1)        / sizeof(char),
        ( sizeof(isbnCode.groupId) - 1)          / sizeof(char),
        ( sizeof(isbnCode.publisherCode) - 1)    / sizeof(char),
        ( sizeof(isbnCode.itemNo) - 1)           / sizeof(char),
        ( sizeof(isbnCode.checkDigit) - 1)       / sizeof(char));

    printf("Please enter ISBN: ");

    while (!isInputValid)
    {
        scanfState = scanf(buffer, 
            &isbnCode.gs1prefix,
            &isbnCode.groupId,
            &isbnCode.publisherCode,
            &isbnCode.itemNo,
            &isbnCode.checkDigit);
        if (scanfState < 5)
        {
            // input invalid
            puts(INPUT_INVALID_MSG);

            // consume trailing invalid input
            char c = '\0';
            while ((c = getchar()) != '\n' && c != EOF) {
                continue;
            }
            continue;
        }
        // consume the trailing new line character left
        // by scanf
        getchar();

        isInputValid = 1;

        // make sure we only got digits in input
        const char **inputStringPtr = &numericLiteralsToValidate[0];
        while (*inputStringPtr != NULL) {
            isInputValid = isInputValid && IsNumericLiteral(*inputStringPtr);
            if (!isInputValid) {
                puts(INPUT_INVALID_MSG);
                break;
            }
            ++inputStringPtr;
        }        
    }
    printf("GS1 prefix: %s\n", isbnCode.gs1prefix);
    printf("Group identifier: %s\n", isbnCode.groupId);
    printf("Publisher code: %s\n", isbnCode.publisherCode);
    printf("Item number: %s\n", isbnCode.itemNo);
    printf("Check digit: %s\n", isbnCode.checkDigit);
    getchar();
    return EXIT_SUCCESS;
}

int IsNumericLiteral(const char* s) {
    if (!s) {
        return 0;
    }
    char c = '\0';
    while ((c = *s) != '\0') {
        if (!isdigit(c)) {
            return 0;
        }
        ++s;
    }
    return 1;
}
