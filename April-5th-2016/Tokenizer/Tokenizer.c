#include <string.h>

#include "Tokenizer.h"

static int *GetTokenCounterAddress(void);

static int GetTokenCount(void);

static int IncrementTokenCount(void);

static int DecrementTokenCount(void);

static char **GetTokenStorageAddress(void);

static void SetTokens(char*);

static char **GetTokenStorageAddress(void) {
    static char* tokens = NULL;
    return &tokens;
}

static void SetTokens(char* tokens) {
    *GetTokenStorageAddress() = tokens;
}

static int *GetTokenCounterAddress(void) {
    static int count = 0;
    return &count;
}

static int GetTokenCount(void) {
    return *GetTokenCounterAddress();
}

static int IncrementTokenCount(void) {
    int *pcount = GetTokenCounterAddress();
    *pcount = *pcount + 1;
    return *pcount;
}

static int DecrementTokenCount(void) {
    int *pcount = GetTokenCounterAddress();
    *pcount = *pcount - 1;
    return *pcount;
}

void TokenizeExpression(char *exp, 
    char *OutResult, 
    size_t OutResultCapacity, 
    int caseSensitive) 
{
    
    size_t len = strlen(exp);

    if (len < 1 || OutResultCapacity < 1) return;
    
    if (OutResultCapacity < 2) {
        SetTokens(OutResult);
        *OutResult = '\0';    
        return;
    }

    OutResult[0] = exp[0];
    IncrementTokenCount();

    size_t i = 1;
    size_t j = 1;
    while (i < len && j < OutResultCapacity - 2) {

        enum CharFamily charFam1 = GetCharFamily(exp[i]);
        enum CharFamily charFam2 = GetCharFamily(exp[i - 1]);

        if (!caseSensitive) {
            // disable case bits to provide case 
            // insensitive comparison
            charFam1 = charFam1 & (~Lower) & (~Upper);
            charFam2 = charFam2 & (~Lower) & (~Upper);
        }

        if (charFam1 == charFam2) {
            OutResult[j] = exp[i];
        }
        else {
            OutResult[j] = '\0';
            ++j; IncrementTokenCount();            
            if (j >= OutResultCapacity - 1) {
                break;
            }
            else {
                OutResult[j] = exp[i];
            }
        }
        ++i, ++j;
    }
    OutResult[j] = '\0';
    SetTokens(OutResult);
}

enum CharFamily GetCharFamily(char c) {
    if (c >= 0x00 && c <= 0x08) {
        return Cntrl;
    }
    else if (c == 0x09) {
        return Cntrl | Blank | Space;
    }
    else if (c >= 0x0A && c <= 0x0D) {
        return Cntrl | Space;
    }
    else if (c >= 0x0E && c <= 0x1F) {
        return Cntrl;
    }
    else if (c == 0x20) {
        return Blank | Space | Print;
    }
    else if (c >= 0x21 && c <= 0x2F) {
        return Punct | Graph | Print;
    }
    else if (c >= 0x30 && c <= 0x39) { 
        return Digit | XDigit | AlNum | Graph | Print;
    }
    else if (c >= 0x3a && c <= 0x40) {
        return Punct | Graph | Print;
    }
    else if (c >= 0x41 && c <= 0x46) {
        return Upper | Alpha | XDigit | AlNum | Graph | Print;
    }
    else if (c >= 0x47 && c <= 0x5A) {
        return Upper | Alpha | AlNum | Graph | Print;
    }
    else if (c >= 0x5B && c <= 0x60) {
        return Punct | Graph | Print;
    }
    else if (c >= 0x61 && c <= 0x66) {
        return Lower | Alpha | XDigit | AlNum | Graph | Print;
    }
    else if (c >= 0x67 && c <= 0x7A) {
        return Lower | Alpha | AlNum | Graph | Print;
    }
    else if (c >= 0x7B && c <= 0x7E) {
        return Punct | Graph | Print;
    }
    else if (c == 0x7F) {
        return Cntrl;
    }
    return Unknown;
}

char* GetNextToken(void) {
    char* currToken = NULL;
    if (GetTokenCount() > 0) {
        currToken = *GetTokenStorageAddress();
        char* nextToken = currToken;
        int currCount = DecrementTokenCount();
        if (currCount > 0) {
            while (*nextToken) ++nextToken;
            ++nextToken;

            SetTokens(nextToken);
        }
    }
    return currToken;
}
