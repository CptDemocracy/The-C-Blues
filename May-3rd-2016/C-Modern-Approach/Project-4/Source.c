/*
K.N.King "C Programming. A Modern Approach."

Programming project 4 p.50

Write a program that prompts the user to enter a telephone
number in the form (xxx) xxx-xxxx and then displays the
number in the form xxx.xxx.xxxx:

"Enter phone number [(xxx) xxx-xxxx]: (404) 817-6900
You entered 404.817.6900
*/

#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

#define BUFFER_SIZE            256
#define INPUT_INVALID_MSG    "Input invalid. Please try again."

struct PhoneNumber
{
    // make sure we add an extra byte to each string
    // to store the null terminating character
    char firstDigitGroup[4];
    char secondDigitGroup[4];
    char thirdDigitGroup[5];
};

int IsNumericLiteral(const char *s);

int main(void)
{
    struct PhoneNumber phoneNumber = { 0 };
    int scanfState = 0;
    int isInputValid = 0;
    const char *numericLiteralsToValidate[] = {
        phoneNumber.firstDigitGroup,
        phoneNumber.secondDigitGroup,
        phoneNumber.thirdDigitGroup,
        NULL // make sure we null-terminate the array
    };
    const char *FORMAT_STRING = "(%%%ds)%%%ds-%%%ds";
    char buffer[BUFFER_SIZE] = { 0 };
    sprintf(buffer, FORMAT_STRING,
        ( sizeof(phoneNumber.firstDigitGroup)    - 1) / sizeof(char),
        ( sizeof(phoneNumber.secondDigitGroup)    - 1) / sizeof(char),
        ( sizeof(phoneNumber.thirdDigitGroup)    - 1) / sizeof(char));

    printf("Enter phone number [(xxx) xxx-xxxx]: ");
    while (!isInputValid) 
    {
        scanfState = scanf(buffer, 
            phoneNumber.firstDigitGroup, 
            phoneNumber.secondDigitGroup,
            phoneNumber.thirdDigitGroup);
        if (scanfState <3) {
            // input invalid
            puts(INPUT_INVALID_MSG);

            // consume trailing invalid input
            char c = '\0';
            while ((c = getchar()) != '\n' && c != EOF) {
                continue;
            }
            continue;
        }
        // consume the trailing new line character
        // left by scanf
        getchar();

        // make sure user only entered digits
        isInputValid = 1;
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
    printf("%s.%s.%s\n", 
        phoneNumber.firstDigitGroup,
        phoneNumber.secondDigitGroup,
        phoneNumber.thirdDigitGroup);
    getchar();
    return EXIT_SUCCESS;
}

int IsNumericLiteral(const char *s) {
    if (!s) return 0;
    char c = '\0';
    while ((c = *s) != '\0') {
        if (!isdigit(c)) {
            return 0;
        }
        ++s;
    }
    return 1;
}
