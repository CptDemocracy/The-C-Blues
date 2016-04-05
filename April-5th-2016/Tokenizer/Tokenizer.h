#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <stdlib.h>

enum CharFamily {
    Unknown = 0x0,
    AlNum = 0x1,
    Alpha = 0x2,
    Blank = 0x4,
    Cntrl = 0x8,
    Digit = 0x10,
    Graph = 0x20,
    Lower = 0x40,
    Print = 0x80,
    Punct = 0x100,
    Space = 0x200,
    Upper = 0x400,
    XDigit = 0x800
};

enum CharFamily GetCharFamily(char c);

void TokenizeExpression(char *exp, 
    char *OutResult, 
    size_t OutResultCapacity, 
    int caseSensitive);

char* GetNextToken(void);

#endif /* TOKENIZER_H */
