#include "Temp.h"

#include <stdarg.h>
#include <stdio.h>

void fn1(size_t argCount, ...) {
    va_list vl;
    va_start(vl, argCount);
    for (size_t i = 0; i < argCount; ++i) {
        int arg = va_arg(vl, int);
        printf("%d ", arg);
    }
    printf("\n");
    va_end(vl);
}

char fn2(size_t argCount, ...) {
    va_list vl;
    va_start(vl, argCount);
    for (size_t i = 0; i < argCount; ++i) {
        char arg = va_arg(vl, char);
        printf("%c ", arg);
    }
    printf("\n");
    va_end(vl);
    return '\0';
}

int fn3(size_t argCount, ...) {
    va_list vl;
    va_start(vl, argCount);
    for (size_t i = 0; i < argCount; ++i) {
        int arg = va_arg(vl, int);
        printf("%d ", arg);
    }
    printf("\n");
    va_end(vl);
    return 0;
}

float fn4(size_t argCount, ...) {
    va_list vl;
    va_start(vl, argCount);
    for (size_t i = 0; i < argCount; ++i) {
        double arg = va_arg(vl, double);
        printf("%f ", arg);
    }
    printf("\n");
    va_end(vl);
    return 0.0F;
}
