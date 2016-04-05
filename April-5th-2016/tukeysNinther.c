#include <string.h>
#include <stdlib.h>
#include <stdio.h>

const void* TukeysNinther(const void* base, int itemCount, int itemSize) {
    int* markup = (int*)calloc(itemCount, sizeof(int));
    if (!markup) {
        errno = ENOMEM;
        return NULL;
    }
    int* SENTINEL = &markup[itemCount];
    int i = 0, j = 0;
    while (j < itemCount) {
        markup[i] = j;
        ++i, j += 2;
    }
    SENTINEL = &markup[i];
    i = 2, j = 0;
    while (&markup[i] < SENTINEL) {
        markup[j] = markup[i];
        i += 3, ++j;
    }
    SENTINEL = &markup[j];
    size_t medianIndex = markup[j / 2];
    free(markup);
    return ((char*)base + medianIndex * itemSize);
}

int main(void)
{
    char chars[] = "RLAPMCGAXZKRBRJJE";
    const char* med = TukeysNinther(chars, strlen(chars), sizeof(char));
    printf("%c\n", *med);
    getchar();
    return 0;
}
