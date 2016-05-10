/*
K.N.King "C Programming. A Modern Approach."
Programming project 1 p.274

"Enter a message: Don't get mad, get even.
Reversal is: .neve teg ,dam teg t'noD
"

*/

#include <stdlib.h>
#include <stdio.h>

int main(void) {
    
    FILE* tmp = tmpfile();
    if (!tmp) {
        return EXIT_FAILURE;
    }

    char c = '\0';

    printf("Please enter a message: ");
    while ((c = getchar()) != '\n' && c != EOF) fputc(c, tmp);

    fpos_t pos = 0;
    (void)fgetpos(tmp, &pos);
    (void)fseek(tmp, 0L, SEEK_SET);

    if (pos > UINT_MAX) return EXIT_FAILURE;

    char* buffer = (char*)calloc((size_t)pos, sizeof(char));
    if (!buffer) {
        return EXIT_FAILURE;
    }

    for (fpos_t i = 0; i < pos; ++i) {
        c = fgetc(tmp);
        buffer[pos - i - 1] = c;
    }

    printf("Reversal is: ");
    for (fpos_t i = 0; i < pos; ++i) {
        printf("%c", buffer[i]);
    }
    putchar('\n');    
    free(buffer);
    fclose(tmp);

    getchar();
    return EXIT_SUCCESS;
}
