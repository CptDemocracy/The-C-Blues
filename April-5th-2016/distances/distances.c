/*
    "Programming Principles" by B.Stroustrup
    p.126 Exercise 3

    Read a sequence of double values into a vector. Think of each value as
    the distance between two cities along a given route. Compute and print
    the total distance (the sum of all distances). Find and print the smallest
    and greatest distance between two neighboring cities. Find and print the
    mean distance between two neighboring cities.
*/

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

#include "DynamicBuffer.h"
#include "Vector.h"

int Sum(const void* base, 
    size_t itemCount, 
    size_t itemSize,
    void (*binarySumFunc)(const void* a, const void* b, void* OutResult),
    void* OutResult);

const void* Max(const void* base,
    size_t itemCount,
    size_t itemSize,
    int (*cmp)(const void* a, const void* b));

const void* Min(const void* base,
    size_t itemCount,
    size_t itemSize,
    int (*cmp)(const void* a, const void* b));

void AddDoubles(const double* a, const double* b, double* OutResult);

int CompareDoubles(const double* a, const double* b);

int main(void)
{

    int error = 0;
    const char* input = NULL;
    static const char* DELIMS = " ";

    struct Vector distancesVector = { 0 };
    error = VectorNew(&distancesVector, sizeof(double), NULL);
    if (error) {
        return error;
    }

    struct DynamicBuffer dynbuffer = { 0 };
    error = DynamicBufferNew(&dynbuffer);
    if (error) {
        return error;
    }

    puts("Please enter a sequences of distances: \n");

    char* buffer = (char*)calloc(1, sizeof(char));

    size_t inputLen = 0;
    int isValid = 0;

    do {
        VectorClear(&distancesVector);

        isValid = 1;

        printf(">>> ");
        DynamicBufferClear(&dynbuffer);

        input = DynamicBufferGetString(&dynbuffer);
        inputLen = strlen(input);

        // store input in a separate directly mutable buffer for validation
        if (inputLen > strlen(buffer)) {
            free(buffer);
            // on the first iteration of the loop, this will ALWAYS
            // be triggered
            buffer = (char*)calloc(inputLen * 2 + 1, sizeof(char));
            if (!buffer) {
                errno = ENOMEM;
                return ENOMEM;
            }
        }
        strcpy(buffer, input);

        // tokenize for validation
        char* token = NULL;
        token = strtok(buffer, DELIMS);
    
        if (!token) {
            // input empty
            fprintf(stderr, "Input invalid.\n");
            isValid = 0;
            continue;
        }

        char* parseEnd = NULL;
        double value = 0.0;

        while (token) {
            
            value = strtod(token, &parseEnd);
            if (value < 0) {
                fprintf(stderr, "Distances between cities cannot be negative.\n");
                isValid = 0;
                break;
            }

            // make sure the token is indeed a number

            // skip whitespace at the end of the token
            char* end = token;
            while (*end) ++end;
            do {
                --end;
            } while (end > token && isspace(*end));
            ++end;

            if (parseEnd != end) {
                // not a valid number
                fprintf(stderr, "Input invalid.\n");
                isValid = 0;
                break;
            }

            VectorAdd(&distancesVector, &value);

            token = strtok(NULL, DELIMS);
        }

        if (!isValid) continue;

        break;

    } while (1);

    free(buffer);

    double dist = 0.0;
    size_t count = VectorGetCount(&distancesVector);

    puts("You have entered the distances below: ");
    for (size_t i = 0; i < count; ++i) {
        VectorGet(&distancesVector, i, &dist);
        printf("%g\n", dist);
    }

    double* distances = (double*)calloc(count, sizeof(double));
    if (!distances) {
        errno = ENOMEM;
        return ENOMEM;
    }

    VectorToArray(&distancesVector, distances, count);

    double sum = 0.0;    
    Sum(distances, count, sizeof(double), AddDoubles, &sum);

    printf("The total sum of all distances is %g.\n", sum);

    double max = 0.0;

    const double* pmax = NULL; 
    pmax = Max(distances, count, sizeof(double), CompareDoubles);
    if (pmax) {
        max = *pmax;
    }

    printf("Greatest distance is %g.\n", max);
    
    double min = 0.0;

    const double* pmin = NULL;
    pmin = Min(distances, count, sizeof(double), CompareDoubles);
    if (pmin) {
        min = *pmin;
    }

    printf("Smallest distance is %g.\n", min);

    double mean = sum / count;

    printf("The mean distance is %g.\n", mean);
    
    free(distances);

    DynamicBufferDispose(&dynbuffer);
    VectorDispose(&distancesVector);

    getchar();
    return 0;
}

int Sum(const void* base, 
    size_t itemCount, 
    size_t itemSize,
    void (*binarySumFunc)(const void* a, const void* b, void* OutResult),
    void* OutResult)
{
    if (!base || itemSize < 1 || !binarySumFunc || !OutResult) {
        errno = EINVAL;
        return EINVAL;
    }
    memset(OutResult, 0, itemSize);
    if (itemCount < 1) {
        return 0;
    }
    else if (itemCount == 1) {
        memcpy(OutResult, base, itemSize);
        return 0;
    }
    memcpy(OutResult, base, itemSize);
    for (size_t i = 1; i < itemCount; ++i) {
        binarySumFunc(OutResult, (char*)base + i * itemSize, OutResult);
    }
    return 0;
}

void AddDoubles(const double* a, const double* b, double* OutResult) {
    if (!a || !b || !OutResult) {
        memset(OutResult, 0, sizeof(double));
        errno = EINVAL;
        return;
    }
    double sum = *a + *b;
    *OutResult = sum;
}

const void* Max(const void* base,
    size_t itemCount,
    size_t itemSize,
    int (*cmp)(const void* a, const void* b))
{
    if (!base || itemCount < 1 || itemSize < 1 || !cmp) {
        errno = EINVAL;
        return NULL;
    }
    const void* max = base;
    const void* cur = NULL;
    for (size_t i = 1; i < itemCount; ++i) {
        cur = (char*)base + i * itemSize;
        if ((*cmp)(cur, max) > 0) {
            max = cur;
        }
    }
    return max;
}

const void* Min(const void* base,
    size_t itemCount,
    size_t itemSize,
    int (*cmp)(const void* a, const void* b))
{
    if (!base || itemCount < 1 || itemSize < 1 || !cmp) {
        errno = EINVAL;
        return NULL;
    }
    const void* min = base;
    const void* cur = NULL;
    for (size_t i = 0; i < itemCount; ++i) {
        cur = (char*)base + i * itemSize;
        if ((*cmp)(cur, min) < 0) {
            min = cur;
        }
    }
    return min;
}

int CompareDoubles(const double* a, const double* b) {
    if (!a && !b) {
        return 0;
    }
    if (!a) {
        return -1;
    }
    if (!b) {
        return 1;
    }
    double n1 = *a;
    double n2 = *b;
    if (n1 > n2) {
        return 1;
    }
    else if (n1 < n2) {
        return -1;
    }
    return 0;
}
