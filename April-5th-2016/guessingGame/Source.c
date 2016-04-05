/*
    "Programming Principles" by B.Stroustrup
    p.126 Exercise 4

    Write a program to play a numbers guessing game. The user thinks of a
    number between 1 and 100 and your program asks questions to figure
    out what the number is (e.g., "Is the number you are thinking of less
    than 50?") . Your program should be able to identify the number after
    asking no more than seven questions. Him: Use the < and <= operators
    and the if·else construct.
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include "DynamicBuffer.h"

// globals are evil, I know, hopefully that "static" there will help my karma...

static const char* YES_CMDS[]   = { "yes", "yep", "ye", "y", "positive", NULL };
static const char* NO_CMDS[]    = { "no", "nope", "ney", "nay", "n", "negative", NULL };
static const char* MAYBE_CMDS[] = { "maybe", NULL };
static const char* FOUND_CMDS[] = { "c", "correct", NULL };

enum Answer { Other = -2, Maybe = -1, No = 0, Yes = 1, Found = 2 } ans = No;

enum Answer AnswerParse(const char* ans);

void ListCommands(const char* cmds[], const char* separator);

int main(void) {

    const int SMALLEST_NUM = 1;
    const int LARGEST_NUM  = 99;

    const int RADIX = 10;

    struct DynamicBuffer dbuffer = { 0 };
    DynamicBufferNew(&dbuffer);

    int lo = SMALLEST_NUM;
    int hi = LARGEST_NUM + 1;
    int mp = (hi + lo) / 2;

    const char* userResponse = NULL;
    const char* separator = " or";

    while (1)
    {

        printf("Is the number you are thinking of less than %d?\n", mp);
        printf("If yes: "); ListCommands(YES_CMDS, separator);
        printf("If no:  "); ListCommands(NO_CMDS, separator);
        printf("If that's the number: "); ListCommands(FOUND_CMDS, separator);
        
        userResponse = DynamicBufferGetString(&dbuffer);

        // parse user response
        ans = AnswerParse(userResponse);
        
        if (ans == Found) {
            printf("Your number was %d.", mp);
            break;
        }
        else if (ans == Yes || ans == No) {
            if (ans == Yes) {
                hi = mp;
            }
            else {
                lo = mp;
            }
            mp = (hi + lo) / 2;
        }
        else if (ans == Maybe) {
            puts("Oh man, you think I'm playing games with you?");
        }        
        else {
            puts("I am sorry, I didn't quite get it, could you please say it again?");
        }        

        if (lo >= hi && ans != Found) {
            printf("It was either %d or %d all along, wasn't it?", mp, rand() % LARGEST_NUM + SMALLEST_NUM);
            break;
        }
    }    

    DynamicBufferDispose(&dbuffer);

    getchar();
    return 0;
}

enum Answer AnswerParse(const char* answer) {
    if (!answer) {
        errno = EINVAL;
        return Other;
    }

    // skip whitespace
    const char* beg = &answer[0];
    while (*beg && isspace(*beg)) ++beg;

    const char* end = beg;
    while (*end) ++end;

    do {
        --end;
    }
    while (end > beg && isspace(*end));
    ++end;

    size_t inputLen = end - beg;

    char* buffer = (char*)calloc(inputLen + 1, sizeof(char));
    if (!buffer) {
        errno = ENOMEM;
        return Other;
    }
    strncpy(buffer, beg, inputLen);

    enum Answer ans = Other;

    int found = 0;
    const char** pcmd = NULL;
    const char* cmd = NULL;

    for (pcmd = &YES_CMDS[0]; pcmd != NULL && *pcmd != NULL && !found; ++pcmd) {
        cmd = *pcmd;
        if (strcmp(cmd, buffer) == 0) {
            ans = Yes;
            found = 1;
            break;
        }
    }
    for (pcmd = &NO_CMDS[0]; pcmd != NULL && *pcmd != NULL && !found; ++pcmd) {
        cmd = *pcmd;
        if (strcmp(cmd, buffer) == 0) {
            ans = No;
            found = 1;
            break;
        }
    }    
    for (pcmd = &MAYBE_CMDS[0]; pcmd != NULL && *pcmd != NULL && !found; ++pcmd) {
        cmd = *pcmd;
        if (strcmp(cmd, buffer) == 0) {
            ans = Maybe;
            found = 1;
            break;
        }
    }
    for (pcmd = &FOUND_CMDS[0]; pcmd != NULL && *pcmd != NULL && !found; ++pcmd) {
        cmd = *pcmd;
        if (strcmp(cmd, buffer) == 0) {
            ans = Found;
            found = 1;
            break;
        }
    }
    free(buffer);
    return ans;
}

void ListCommands(const char* cmds[], const char* separator) {
    if (!cmds || !separator) return;
    for (const char** pcmd = &cmds[0]; *pcmd != NULL; ++pcmd) {
        const char* cmd = *pcmd;
        if (*(pcmd + 1) == NULL) {
            // no need for the separator for the last entry
            printf("\"%s\"", cmd);
        }
        else {
            printf("\"%s\"%s ", cmd, separator);
        }
    }
    putchar('\n');
}
