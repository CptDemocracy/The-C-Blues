/*
K.N.King "C Programming. A Modern Approach."
Programming project 4 p.96

Here's a simplified version of the Beaufort scale,
which is used to estimate wind force:

Speed(knots)    Description
Less than 1     Calm
1-3             Light air
4-27            Breeze
28-47           Gale
48-63           Storm
Above 63        Hurricane

Write a program that asks the user to enter 
a wind speed (in knots), then displays the
corresponding description.
*/

#include <stdlib.h>
#include <stdio.h>

/*
Arguments: 
    windSpeedInKnots : int - wind speed in knots

Pre-condition:
    windSpeedInKnots : int cannot be negative.
Post-condition:
    Returns a readonly string with a wind force 
    description according to the Beaufort scale:

    Speed(knots)    Description
    Less than 1     Calm
    1-3             Light air
    4-27            Breeze
    28-47           Gale
    48-63           Storm
    Above 63        Hurricane

WARNING:
    The string is readonly and must not be 
    changed by the caller.
*/
const char* GetWindForceDescription(int windSpeedInKnots);

int main(void) 
{
    int windSpeedInKnots = 0;
    int isInputValid = 0;
    char c = '\0';
    const char* descr = NULL;

    while (!isInputValid)
    {
        printf("Please enter the speed of wind (in knots): ");
        while ( scanf("%d", &windSpeedInKnots) < 1) {
            puts("Input invalid. Please make sure wind speed is an integer.");

            // discard trailing invalid input left by scanf
            while ( (c = getchar()) != '\n' && c != EOF) continue;
        }
        // discard the new line/whitespace chars left by scanf
        while ( (c = getchar()) != '\n' && c != EOF) continue;

        if (windSpeedInKnots < 0) {
            puts("Input invalid. The speed of wind cannot be negative.");
        } else {
            isInputValid = 1;
        }
    }
    descr = GetWindForceDescription(windSpeedInKnots);
    printf("Wind speed: %d knots\n", windSpeedInKnots);
    printf("Description: %s\n", descr);
    getchar();
    return EXIT_SUCCESS;
}

/*
    Speed(knots)    Description
    Less than 1     Calm
    1-3             Light air
    4-27            Breeze
    28-47           Gale
    48-63           Storm
    Above 63        Hurricane
*/
const char* GetWindForceDescription(int windSpeedInKnots) {
    if (windSpeedInKnots < 0) {
        return NULL;
    }
    if (windSpeedInKnots < 1) {
        return "Calm";
    }
    else if (windSpeedInKnots < 4) {
        return "Light air";
    }
    else if (windSpeedInKnots < 28) {
        return "Breeze";
    }
    else if (windSpeedInKnots < 48) {
        return "Gale";
    }
    else if (windSpeedInKnots < 64) {
        return "Storm";
    }
    return "Hurricane";
}
