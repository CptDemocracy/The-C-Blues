#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <stdio.h>

/*K&R C (Dennis M. Ritchie & Brian W. Kernighan)
 Exercise 5-14. Modify the sort program to handle a -r flag, 
 which indicates sorting in reverse (decreasing) order. 
 Be sure that -r works with -n.

 (-n will sort the input lines numerically instead of
    lexicographically.)
*/

#define BUFFER_SIZE 64

int Merge(void* base, int itemSize, int lo, int hi, int (*cmp)(const void*, const void*));

int MergeSort(void* base, int itemSize, int lo, int hi, int (*cmp)(const void*, const void*));

int CompareStringsGivenPointers(const char** ptrs1, const char** ptrs2);

int ReverseCompareStringsGivenPointers(const char** ptrs1, const char** ptrs2);

int ParseCompareDoubles(const char** ptrs1, const char** ptrs2);

int ParseReverseCompareDoubles(const char** ptrs1, const char** ptrs2);

int main(int argc, const char* argv[]) {
    
    int (*pCmpFunc)(const char**, const char**) = NULL;

    if (argc > 0) {

        int areArgsValid = 1;

        const char* REV_SORT_ARG = "-r";
        const char* NUM_SORT_ARG = "-n";
        
        if (argc == 2) {
            if (strcmp(argv[1], REV_SORT_ARG) == 0) {
                pCmpFunc = &ReverseCompareStringsGivenPointers;
            }
            else if (strcmp(argv[1], NUM_SORT_ARG) == 0) {
                pCmpFunc = &ParseCompareDoubles;
            }
            else {
                areArgsValid = 0;
            }
        }
        else if (argc == 3) {
            if ((strcmp(argv[1], REV_SORT_ARG) == 0 ||
                 strcmp(argv[2], REV_SORT_ARG) == 0) 
                && (strcmp(argv[1], NUM_SORT_ARG) == 0 ||
                    strcmp(argv[2], NUM_SORT_ARG) == 0))
            {
                pCmpFunc = &ParseReverseCompareDoubles;
            }
            else {
                areArgsValid = 0;
            }            
        }

        if (!areArgsValid) {
            fprintf(stderr, "Usage: sort [-r|-n] [-r|-n]");
            return 1;
        }

    } else {
        pCmpFunc = &CompareStringsGivenPointers;
    }

    char buffer[BUFFER_SIZE] = { 0 };
    size_t inputLen = 0;

    size_t lineCount = 0;
    size_t lineCapacity = 4;
    char** lines = (char**)calloc(lineCapacity, sizeof(char*));
    if (!lines) {
        errno = ENOMEM;
        return ENOMEM;
    }
    while (1)
    {
        puts("Please enter a line of text or if you are ready to sort, please enter \"<done>\".");
        puts("Enter <q> to exit.");
        while (1)
        {            

            printf(">>> ");

            if (!fgets(buffer, BUFFER_SIZE, stdin)) {
                puts("An error occured trying to read input. Please contact your tech support.");
                return 1;
            }

            inputLen = strlen(buffer);
            if (BUFFER_SIZE > 1 && buffer[inputLen - 1] == '\n') {
                buffer[inputLen - 1] = '\0';
            }
            if (strcmp(buffer, "<done>") == 0) {
                break;
            }
            else if (strcmp(buffer, "<q>") == 0) {
                puts("Thank you for using our application! :)");

                // dispose of strings
                for (size_t i = 0; i < lineCount; ++i) {
                    free(lines[i]);
                }
                return 0;

            }
            if (lineCount >= lineCapacity) {
                size_t newLineCapacity = lineCapacity * 2;
                char** newLines = (char**)calloc(lineCapacity, sizeof(char*));
                if (!newLines) {
                    errno = ENOMEM;
                    return ENOMEM;
                }
                memcpy(newLines, lines, lineCount * sizeof(char*));
                free(lines);
                lines = newLines;
                lineCapacity = newLineCapacity;
            }            
            lines[lineCount] = (char*)calloc(inputLen + 1, sizeof(char));
            strncpy(lines[lineCount], buffer, inputLen + 1);
            ++lineCount;
        }

        if (lineCount < 1) {
            puts("Received no input.");
        } else {
            // sort
            MergeSort(lines, sizeof(char**), 0, lineCount, pCmpFunc);

            // list the items
            for (size_t i = 0; i < lineCount; ++i) {
                printf("%d. %s\n", i, lines[i]);
            }

            // dispose of strings
            for (size_t i = 0; i < lineCount; ++i) {
                free(lines[i]);
            }
            lineCount = 0;
        }
    }
    free(lines);
    
    getchar();
    return 0;
}

int ParseCompareDoubles(const char** ptrs1, const char** ptrs2) {
    
    if (!ptrs1 && !ptrs2) return 0;
    if (!ptrs1) return -1;
    if (!ptrs2) return 1;
    
    double n1 = 0.0;
    double n2 = 0.0;

    int isN1Valid = 1;
    int isN2Valid = 1;

    char* parseEnd = NULL;
    const char* end = 0;

    const char* s1 = *ptrs1;
    
    // trim whitespace at the end
    end = &s1[strlen(s1) - 1];
    while (isblank(*end)) --end;
    
    // at this point we have consumed
    // (hopefully) a num char, go a byte
    // forward, because this is where
    // strtod will be pointing to if the
    // number is indeed in a correct format
    ++end;

    n1 = strtod(s1, &parseEnd);
    if (end != parseEnd) {
        // the number was either not a number
        // or in an incorrect format
        isN1Valid = 0;
    }
    
    const char* s2 = *ptrs2;

    // trim whitespace at the end
    end = &s2[strlen(s2) - 1];
    while (isblank(*end)) --end;
    
    // at this point we have consumed
    // (hopefully) a num char, go a byte
    // forward, because this is where
    // strtod will be pointing to if the
    // number is indeed in a correct format
    ++end;

    n2 = strtod(s2, &parseEnd);
    if (end != parseEnd) {
        // the number was either not a number
        // or in an incorrect format
        isN2Valid = 0;
    }

    // we originally wanted to return a -2 to signalize an error,
    // however, this opens up to a situation where clients might
    // process a cmp function explicitly, e.g. cmp(...) == -1,
    // cmp(...) == 1, cmp(...) == 0, instead of cmp(...) < 0,
    // cmp(...) > 0, cmp(...) == 0
    // this would be a difficult bug to track down, so we treat
    // invalid input as "inferior" to the valid one, that is
    // cmp(valid, invalid) > 0, cmp(invalid, valid) < 0, 
    // cmp(invalid, invalid) == 0
    
    if (!isN1Valid && !isN2Valid) return 0;
    if (!isN1Valid) return -1;
    if (!isN2Valid) return 1;
    
    // all good here, start comparing
    if (n1 > n2) return 1;
    else if (n2 > n1) return -1;
    return 0;        
}

int ParseReverseCompareDoubles(const char** ptrs1, const char** ptrs2) {
    return -ParseCompareDoubles(ptrs1, ptrs2);    
}

int CompareStringsGivenPointers(const char** ptrs1, const char** ptrs2) {
    return strcmp(*ptrs1, *ptrs2);
}

int ReverseCompareStringsGivenPointers(const char** ptrs1, const char** ptrs2) {
    return -CompareStringsGivenPointers(ptrs1, ptrs2);
}

int Merge(void* base, int itemSize, int lo, int hi, int (*cmp)(const void*, const void*))
{
    if (!base || !cmp || itemSize < 1) {
        errno = EINVAL;
        return EINVAL;
    }
    if (hi - lo < 2) {
        return 0;
    }
    int count = hi - lo;
    int mid = (hi + lo) / 2;
    int i = lo;
    int j = mid;    
    void* aux = calloc(hi - lo, itemSize);
    if (!aux) {
        errno = ENOMEM;
        return ENOMEM;
    }
    void* dest = aux;
    for (int k = 0; k < count; ++k) {
        if (i >= mid) {
            memcpy(dest, (char*)base + itemSize * j, itemSize);
            ++j;
        }
        else if (j >= hi) {
            memcpy(dest, (char*)base + itemSize * i, itemSize);
            ++i;
        }
        else if ((*cmp)((char*)base + itemSize * i, (char*)base + itemSize * j) > 0) 
        {
            memcpy(dest, (char*)base + itemSize * j, itemSize);
            ++j;
        }
        else {
            memcpy(dest, (char*)base + itemSize * i, itemSize);
            ++i;
        }
        dest = (char*)dest + itemSize;
    }
    memcpy((char*)base + lo * itemSize, aux, itemSize * count);
    free(aux);
    return 0;
}

int MergeSort(void* base, int itemSize, int lo, int hi, int (*cmp)(const void*, const void*)) 
{
    if (!base || itemSize < 1 || !cmp) {
        errno = EINVAL;
        return EINVAL;
    }
    if (hi - lo < 2) {
        return 0;
    }
    MergeSort(base, itemSize, lo, (hi + lo) / 2, cmp);
    MergeSort(base, itemSize, (hi + lo) / 2, hi, cmp);
    Merge(base, itemSize, lo, hi, cmp);
    return 0;
}
