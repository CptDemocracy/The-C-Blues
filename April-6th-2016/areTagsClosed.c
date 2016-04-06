#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

#include "TagPair.h"
#include "Stack.h"

int AreTagsClosed(const char* text, const struct TagPair* tagPair) {
    if (!text || !tagPair) {
        errno = EINVAL;
        return EINVAL;
    }

    // tags stack will keep references to the tags
    // found in text
    struct Stack tags = { 0 };
    int state = StackNew(&tags, sizeof(char*), NULL);
    if (state != 0) {
        return state;
    }

    size_t textLen = strlen(text);
    size_t openingTagLen = strlen(tagPair->openingTag);
    size_t closingTagLen = strlen(tagPair->closingTag);

    int tagFound = 0;

    for (size_t i = 0; i < textLen; ++i) {
        if (i <= textLen - openingTagLen &&
            (strncmp(tagPair->openingTag, &text[i], openingTagLen) == 0)) 
        {
            tagFound = 1;
            StackPush(&tags, &tagPair->openingTag);
        }
        else if (i <= textLen - closingTagLen &&
                (strncmp(tagPair->closingTag, &text[i], closingTagLen) == 0))
        {
            tagFound = 1;
            if (StackGetCount(&tags) <= 0) return 0;            

            StackPop(&tags, NULL);
        }
    }

    size_t stackCount = StackGetCount(&tags);
    StackDispose(&tags);

    if (!tagFound) return -1;

    return stackCount == 0;
}

int AreTagsClosedInFile(const char* filepath, const struct TagPair* tags, size_t tagsLen) {
    if (!filepath || !tags || tagsLen <= 0) {
        errno = EINVAL;
        return 0;
    }

    FILE* file = fopen(filepath, "r");
    if (!file) return 0;

    // bufferSize will have the size of the longest tag (regardless of
    // whether it is opening or closing)
    size_t bufferSize = 0;    

    size_t openingTagLen = 0, closingTagLen = 0;
    for (size_t i = 0; i < tagsLen; ++i) {
        openingTagLen = strlen(tags[i].openingTag);
        closingTagLen = strlen(tags[i].closingTag);
        if (openingTagLen > bufferSize) bufferSize = openingTagLen;
        if (closingTagLen > bufferSize) bufferSize = closingTagLen;
    }

    // tagStack will keep references to the tags
    // found in text
    struct Stack tagStack = { 0 };
    int state = StackNew(&tagStack, sizeof(char*), NULL);
    if (state != 0) {
        errno = state;
        return 0;
    }

    // setvbuf call requires bufferSize to have a min size of 2
    // we need support for 1 byte long buffers, hence we handle
    // buffering on our own

    char* buffer = (char*)calloc(bufferSize, sizeof(char));
    if (!buffer) {
        errno = ENOMEM;
        return 0;
    }

    size_t bufferCount = 0;

    char c = 0;
    while (c != EOF) {
        if (bufferCount >= bufferSize) {
            size_t n = 0;
            while (n < bufferCount) {
                int found = 0;
                for (size_t m = 0; m < tagsLen; ++m) {
                    openingTagLen = strlen(tags[m].openingTag);
                    closingTagLen = strlen(tags[m].closingTag);
                    if (n <= bufferCount - openingTagLen &&
                        (strncmp(&buffer[n], tags[m].openingTag, openingTagLen) == 0))
                    {
                        StackPush(&tagStack, &tags[m].openingTag);
                        n += openingTagLen;
                        found = 1;
                        break;
                    }
                    else if (n <= bufferCount - closingTagLen &&
                             (strncmp(&buffer[n], tags[m].closingTag, closingTagLen) == 0))
                    {
                        char* lastOpeningTag = NULL;
                        StackPeek(&tagStack, &lastOpeningTag);
                        int tagsMatch = (strncmp(lastOpeningTag, tags[m].openingTag, openingTagLen) == 0);

                        if (StackGetCount(&tagStack) <= 0 || !tagsMatch) {
                            StackDispose(&tagStack);
                            fclose(file);
                            free(buffer);
                            return 0;
                        }
                        StackPop(&tagStack, NULL);
                        n += closingTagLen;
                        found = 1;
                        break;
                    }
                }
                if (!found) ++n;
            }
            bufferCount = 0;
        }
        c = fgetc(file);
        buffer[bufferCount] = c;
        ++bufferCount;
    }

    size_t stackCount = StackGetCount(&tagStack);

    StackDispose(&tagStack);

    fclose(file);
    free(buffer);

    return stackCount == 0;
}

int main(void) {
    
    /*struct TagPair parens = { 0 };
    TagPairNew(&parens, "(", ")");
    AreTagsClosed("((_)(__))", &parens);
    TagPairDispose(&parens);*/

    struct TagPair tags[] = {
        { .openingTag = "(", .closingTag = ")" },
        { .openingTag = "{", .closingTag = "}" }
    };
    
    const char* path = "test.c";

    int areTagsClosed = AreTagsClosedInFile(path, tags, 2);

    return 0;
}
