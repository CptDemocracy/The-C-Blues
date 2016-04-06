#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>

int main(void)
{
    static const char *ASCII_CHARSET = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    const size_t ASCII_CHARSET_COUNT = strlen(ASCII_CHARSET);

    unsigned int seed = (unsigned int)time(NULL);

    size_t randStringCount = 10;
    size_t randStringLength = 10;

    char *stringBuffer = (char*)calloc(randStringCount * (randStringLength + 1), sizeof(char*));
    if (!stringBuffer) {
        errno = ENOMEM;
        return errno;
    }
    for (size_t i = 0; i < randStringCount; ++i) {
        for (size_t j = 0; j < randStringLength; ++j) {
            size_t randIndex = rand() % ASCII_CHARSET_COUNT;
            stringBuffer[i * (randStringLength + 1) + j] = ASCII_CHARSET[randIndex];
        }
        puts(&stringBuffer[i * (randStringLength + 1)]);
    }

    free(stringBuffer);
    getchar();

    return 0;
}
