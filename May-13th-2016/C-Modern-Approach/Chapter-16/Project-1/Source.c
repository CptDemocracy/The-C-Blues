/*
K.N.King "C Programming. A Modern Approach."
Programming project 1 p.412

Write a program that asks the user to enter an international
dialing code and then looks it up in the country_codes array.
If it finds the code, the program should display the name of
the corresponding country; if not, the program should print
an error message.

*/

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

#include "Dictionary.h"
#include "DynamicBuffer.h"

enum Country {
    Country_Argentina,
    Country_Bangladesh,
    Country_Brazil,
    Country_Burma,
    Country_China,
    Country_Colombia,
    Country_Congo,
    Country_Egypt,
    Country_Ethiopia,
    Country_France,
    Country_Germany,
    Country_India,
    Country_Indonesia,
    Country_Iran,
    Country_Italy,
    Country_Japan,
    Country_Mexico,
    Country_Nigeria,
    Country_Pakistan,
    Country_Philippines,
    Country_Poland,
    Country_Russia,
    Country_SouthAfrica,
    Country_SouthKorea,
    Country_Spain,
    Country_Sudan,
    Country_Thailand,
    Country_Turkey,
    Country_Ukraine,
    Country_UK,
    Country_US,
    Country_Vietnam
};

const char* COUNTRY_STRING_TABLE[] = {
    [Country_Argentina]        = "Argentina",
    [Country_Bangladesh]    = "Bangladesh",
    [Country_Brazil]        = "Brazil",
    [Country_Burma]            = "Burma (Myanmar)",
    [Country_China]            = "China",
    [Country_Colombia]        = "Colombia",
    [Country_Congo]            = "Congo, Dem. Rep. of",
    [Country_Egypt]            = "Egypt",
    [Country_Ethiopia]        = "Ethiopia",
    [Country_France]        = "France",
    [Country_Germany]        = "Germany",
    [Country_India]            = "India",
    [Country_Indonesia]        = "Indonesia",
    [Country_Iran]            = "Iran",
    [Country_Italy]            = "Italy",
    [Country_Japan]            = "Japan",
    [Country_Mexico]        = "Mexico",
    [Country_Nigeria]        = "Nigeria",
    [Country_Pakistan]        = "Pakistan",
    [Country_Philippines]    = "Philippines",
    [Country_Poland]        = "Poland",
    [Country_Russia]        = "Russia",
    [Country_SouthAfrica]    = "South Africa",
    [Country_SouthKorea]    = "South Korea",
    [Country_Spain]            = "Spain",
    [Country_Sudan]            = "Sudan",
    [Country_Thailand]        = "Thailand",
    [Country_Turkey]        = "Turkey",
    [Country_Ukraine]        = "Ukraine",
    [Country_UK]            = "United Kingdom",
    [Country_US]            = "United States of America",
    [Country_Vietnam]        = "Vietnam",
};

const char* COUNTRY_CODES[] = {
    [Country_Argentina]        = "54",
    [Country_Bangladesh]    = "880",
    [Country_Brazil]        = "55",
    [Country_Burma]            = "95",
    [Country_China]            = "86",
    [Country_Colombia]        = "57",
    [Country_Congo]            = "243",
    [Country_Egypt]            = "20",
    [Country_Ethiopia]        = "251",
    [Country_France]        = "33",
    [Country_Germany]        = "49",
    [Country_India]            = "91",
    [Country_Indonesia]        = "62",
    [Country_Iran]            = "98",
    [Country_Italy]            = "39",
    [Country_Japan]            = "81",
    [Country_Mexico]        = "52",
    [Country_Nigeria]        = "234",
    [Country_Pakistan]        = "92",
    [Country_Philippines]    = "63",
    [Country_Poland]        = "48",
    [Country_Russia]        = "7",
    [Country_SouthAfrica]    = "27",
    [Country_SouthKorea]    = "82",
    [Country_Spain]            = "34",
    [Country_Sudan]            = "249",
    [Country_Thailand]        = "66",
    [Country_Turkey]        = "90",
    [Country_Ukraine]        = "380",
    [Country_UK]            = "44",
    [Country_US]            = "1",
    [Country_Vietnam]        = "84",
};

int CountryCodeDictionaryInitialize(struct Dictionary* dict);

int main(void) {

    struct DynamicBuffer dynBuffer = { 0 };
    struct Dictionary countryCodeDict = { 0 };
    enum Country country = 0;
    const char* countryString = NULL;
    const char* countryCodeString = NULL;

    int exitState = EXIT_SUCCESS;

    do {
        if (DynamicBufferNew(&dynBuffer) != 0) {
            exitState = EXIT_FAILURE;
            break;
        }

        if (DictionaryNew(&countryCodeDict, 4U, sizeof(char*), sizeof(enum Country)) != 0) {
            exitState = EXIT_FAILURE;
            break;
        }
        (void) CountryCodeDictionaryInitialize(&countryCodeDict);

        while (1)
        {
            (void) printf("Please enter a country code (or press Enter to quit): ");

            countryCodeString = DynamicBufferGetString(&dynBuffer);
            if (!countryCodeString) {
                exitState = EXIT_FAILURE;
                break;
            }
            
            // skip whitespace in the beginning of the string
            while (isspace(*countryCodeString)) ++countryCodeString;

            if (*countryCodeString == '\0') {
                (void) printf("Thank you for using our application!\n");
                break;
            } else if (DictionaryGet(&countryCodeDict, countryCodeString, &country)) {
                countryString = COUNTRY_STRING_TABLE[country];
                (void) printf("%s\n", countryString);
            } else {
                (void) fprintf(stderr, "Country code not found in the database. Please try again.\n");
            }
            (void) DynamicBufferClear(&dynBuffer);
        }
        if (exitState == EXIT_FAILURE) {
            break;
        }

    } while (0);

    DynamicBufferDispose(&dynBuffer);
    DictionaryDispose(&countryCodeDict);

    (void) getchar();

    return exitState;
}

int CountryCodeDictionaryInitialize(struct Dictionary* dict) {
    if (!dict) {
        return 1;
    }

    int isAddSuccessful = 0;
    enum Country country = 0;
    
    do {
        country = Country_Argentina;
        isAddSuccessful = DictionaryAdd(dict, COUNTRY_CODES[Country_Argentina], &country);
        if (!isAddSuccessful) break;

        country = Country_Bangladesh;
        isAddSuccessful = DictionaryAdd(dict, COUNTRY_CODES[Country_Bangladesh], &country);
        if (!isAddSuccessful) break;

        country = Country_Brazil;
        isAddSuccessful = DictionaryAdd(dict, COUNTRY_CODES[Country_Brazil], &country);
        if (!isAddSuccessful) break;

        country = Country_Burma;
        isAddSuccessful = DictionaryAdd(dict, COUNTRY_CODES[Country_Burma], &country);
        if (!isAddSuccessful) break;

        country = Country_China;
        isAddSuccessful = DictionaryAdd(dict, COUNTRY_CODES[Country_China], &country);
        if (!isAddSuccessful) break;

        country = Country_Colombia;
        isAddSuccessful = DictionaryAdd(dict, COUNTRY_CODES[Country_Colombia], &country);
        if (!isAddSuccessful) break;

        country = Country_Congo;
        isAddSuccessful = DictionaryAdd(dict, COUNTRY_CODES[Country_Congo], &country);
        if (!isAddSuccessful) break;

        country = Country_Egypt;
        isAddSuccessful = DictionaryAdd(dict, COUNTRY_CODES[Country_Egypt], &country);
        if (!isAddSuccessful) break;

        country = Country_Ethiopia;
        isAddSuccessful = DictionaryAdd(dict, COUNTRY_CODES[Country_Ethiopia], &country);
        if (!isAddSuccessful) break;

        country = Country_France;
        isAddSuccessful = DictionaryAdd(dict, COUNTRY_CODES[Country_France], &country);
        if (!isAddSuccessful) break;

        country = Country_Germany;
        isAddSuccessful = DictionaryAdd(dict, COUNTRY_CODES[Country_Germany], &country);
        if (!isAddSuccessful) break;

        country = Country_India;
        isAddSuccessful = DictionaryAdd(dict, COUNTRY_CODES[Country_India], &country);
        if (!isAddSuccessful) break;

        country = Country_Indonesia;
        isAddSuccessful = DictionaryAdd(dict, COUNTRY_CODES[Country_Indonesia], &country);
        if (!isAddSuccessful) break;

        country = Country_Iran;
        isAddSuccessful = DictionaryAdd(dict, COUNTRY_CODES[Country_Iran], &country);
        if (!isAddSuccessful) break;

        country = Country_Italy;
        isAddSuccessful = DictionaryAdd(dict, COUNTRY_CODES[Country_Italy], &country);
        if (!isAddSuccessful) break;

        country = Country_Japan;
        isAddSuccessful = DictionaryAdd(dict, COUNTRY_CODES[Country_Japan], &country);
        if (!isAddSuccessful) break;

        country = Country_Mexico;
        isAddSuccessful = DictionaryAdd(dict, COUNTRY_CODES[Country_Mexico], &country);
        if (!isAddSuccessful) break;

        country = Country_Nigeria;
        isAddSuccessful = DictionaryAdd(dict, COUNTRY_CODES[Country_Nigeria], &country);
        if (!isAddSuccessful) break;

        country = Country_Pakistan;
        isAddSuccessful = DictionaryAdd(dict, COUNTRY_CODES[Country_Pakistan], &country);
        if (!isAddSuccessful) break;

        country = Country_Philippines;
        isAddSuccessful = DictionaryAdd(dict, COUNTRY_CODES[Country_Philippines], &country);
        if (!isAddSuccessful) break;

        country = Country_Poland;
        isAddSuccessful = DictionaryAdd(dict, COUNTRY_CODES[Country_Poland], &country);
        if (!isAddSuccessful) break;

        country = Country_Russia;
        isAddSuccessful = DictionaryAdd(dict, COUNTRY_CODES[Country_Russia], &country);
        if (!isAddSuccessful) break;

        country = Country_SouthAfrica;
        isAddSuccessful = DictionaryAdd(dict, COUNTRY_CODES[Country_SouthAfrica], &country);
        if (!isAddSuccessful) break;

        country = Country_SouthKorea;
        isAddSuccessful = DictionaryAdd(dict, COUNTRY_CODES[Country_SouthKorea], &country);
        if (!isAddSuccessful) break;

        country = Country_Spain;
        isAddSuccessful = DictionaryAdd(dict, COUNTRY_CODES[Country_Spain], &country);
        if (!isAddSuccessful) break;

        country = Country_Sudan;
        isAddSuccessful = DictionaryAdd(dict, COUNTRY_CODES[Country_Sudan], &country);
        if (!isAddSuccessful) break;

        country = Country_Thailand;
        isAddSuccessful = DictionaryAdd(dict, COUNTRY_CODES[Country_Thailand], &country);
        if (!isAddSuccessful) break;

        country = Country_Turkey;
        isAddSuccessful = DictionaryAdd(dict, COUNTRY_CODES[Country_Turkey], &country);
        if (!isAddSuccessful) break;

        country = Country_Ukraine;
        isAddSuccessful = DictionaryAdd(dict, COUNTRY_CODES[Country_Ukraine], &country);
        if (!isAddSuccessful) break;
    
        country = Country_UK;
        isAddSuccessful = DictionaryAdd(dict, COUNTRY_CODES[Country_UK], &country);
        if (!isAddSuccessful) break;

        country = Country_US;
        isAddSuccessful = DictionaryAdd(dict, COUNTRY_CODES[Country_US], &country);
        if (!isAddSuccessful) break;

        country = Country_Vietnam;
        isAddSuccessful = DictionaryAdd(dict, COUNTRY_CODES[Country_Vietnam], &country);
        if (!isAddSuccessful) break;
    } while (0);

    return isAddSuccessful;
}
