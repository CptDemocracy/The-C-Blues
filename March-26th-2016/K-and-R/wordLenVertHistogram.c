#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <errno.h>

/* K&R C (Dennis M. Ritchie & Brian W. Kernighan)
 Exercise 1-13. Write a program to print a histogram of the lengths 
 of words in its input. It is easy to draw the histogram with the 
 bars horizontal; a vertical orientation is more challenging.
*/

int main(int argc, const char** argv) {

    const char HIST_CHAR = '*';
    const char EXIT_CHAR = EOF;

    char c = 0;

    size_t  pWLensCapacity = 4u;
    size_t* pWLens = (size_t*)calloc(pWLensCapacity, sizeof(size_t));
    if (!pWLens) {
        errno = ENOMEM;
        return 1;
    }

    size_t pWLensCount = 0u;

    size_t wlen = 0u;
    size_t maxlen = 0u;
    
    int canExit = 0;

    while (!canExit)
    {
        // print histo
        while (maxlen > 0u) {
            for (size_t i = 0u; i < pWLensCount; ++i) {
                if (pWLens[i] == maxlen) {
                    pWLens[i] = pWLens[i] > 0 ? --pWLens[i] : 0;
                    putchar(HIST_CHAR);
                } else {
                    putchar(' ');
                }
            }
            putchar('\n');
            --maxlen;
        }

        memset(pWLens, 0, pWLensCapacity * sizeof(size_t));
        pWLensCount = 0u;

        printf(">>> ");
    
        while (1) {
            c = getchar();

            if (c == EXIT_CHAR) {
                canExit = 1;

                // flush redundant input in the buffer if any
                while (getchar() != '\n') continue;

                break;
            }
            else if (isspace(c) || c == '\n') {
                if (pWLensCount >= pWLensCapacity) {
                    pWLensCapacity *= 2u;
                    size_t* newPWLens = (size_t*)calloc(pWLensCapacity, sizeof(size_t));
                    if (!newPWLens) {
                        errno = ENOMEM;
                        return 1;
                    }
                    memcpy(newPWLens, pWLens, pWLensCount * sizeof(size_t));
                    free(pWLens);
                    pWLens = newPWLens;
                }
                pWLens[pWLensCount] = wlen;
                ++pWLensCount;

                if (wlen > maxlen) {
                    maxlen = wlen;
                }
                wlen = 0u;
                
                if (c == '\n') break;

            } else {
                ++wlen;
            }
        }
    }
    free(pWLens); 
    pWLens = NULL;
    return 0;
}
