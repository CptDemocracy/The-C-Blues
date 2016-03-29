#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>

/* K&R C (Dennis M. Ritchie & Brian W. Kernighan)
 Exercise 3-1. Our binary search makes two tests inside the loop, when one 
 would suffice (at the price of more tests outside.) Write a version with 
 only one test inside the loop and measure the difference in run-time.
*/

int CompareInts(const int* ptr1, const int* ptr2) {
    if (!ptr1 && !ptr2) {
        return 0;
    }
    if (!ptr1) {
        return -1;
    }
    if (!ptr2) {
        return 1;
    }
    int n = *ptr1;
    int m = *ptr2;
    if (n == m) {
        return 0;
    }
    if (n >  m) {
        return 1;
    }
    return -1;
}

int BSearch1(const void* key, 
    const void* base, 
    size_t itemCount, 
    size_t itemSize, 
    int (*cmp) (const void*, const void*)) 
{
    
    static const int ERROR = -2;    
    static const int NOT_FOUND = -1;

    if (!key) {
        errno = EINVAL;
        return ERROR;
    }
    if (!base) {
        errno = EINVAL;
        return ERROR;
    }
    if (!cmp) {
        errno = EINVAL;
        return ERROR;
    }

    size_t lo = 0;
    size_t hi = itemCount;    
    while (lo < hi) {
        size_t mid = (hi + lo) / 2;
        int compar = (*cmp)((char*)base + mid * itemSize, key);
        if (compar > 0) {
            hi = mid - 1;
        }
        else if (compar < 0) {
            lo = mid + 1;
        }
        else {
            return mid;
        }
    }
    return NOT_FOUND;
}

int BSearch2(const void* key,
    const void* base,
    size_t itemCount,
    size_t itemSize,
    int (*cmp)(const void*, const void*))
{
    static const int ERROR = -2;    
    static const int NOT_FOUND = -1;

    if (!key) {
        errno = EINVAL;
        return ERROR;
    }
    if (!base) {
        errno = EINVAL;
        return ERROR;
    }
    if (!cmp) {
        errno = EINVAL;
        return ERROR;
    }

    size_t lo = 0;
    size_t hi = itemCount;
    size_t mid = (hi + lo) / 2;
    int compar = (*cmp)((char*)base + mid * itemSize, key);    
    while (lo < hi && compar != 0) {        
        if (compar > 0) {
            hi = mid - 1;
        }
        else {
            lo = mid + 1;
        }
        mid = (hi + lo) / 2;
        compar = (*cmp)((char*)base + mid * itemSize, key);
    } 
    if (compar == 0) {
        return mid;
    }
    return -1;
}

int BSearchRecHelper(const void* key,
    const void* base,
    size_t lo,
    size_t hi,
    size_t itemSize,
    int (*cmp) (const void*, const void*))
{

    if (lo >= hi) {
        return -1;
    }

    size_t mid = (lo + hi) / 2;
    int compar = (*cmp)((char*)base + mid * itemSize, key);
    if (compar > 0) {
        return BSearchRecHelper(key, base, lo, mid - 1, itemSize, cmp);
    }
    else if (compar < 0) {
        return BSearchRecHelper(key, base, mid + 1, hi, itemSize, cmp);
    }
    return mid;
}

int BSearchRec(const void* key,
    const void* base,
    size_t itemCount,
    size_t itemSize,
    int (*cmp)(const void*, const void*))
{
    static const int ERROR = -2;    
    static const int NOT_FOUND = -1;

    if (!key) {
        errno = EINVAL;
        return ERROR;
    }
    if (!base) {
        errno = EINVAL;
        return ERROR;
    }
    if (!cmp) {
        errno = EINVAL;
        return ERROR;
    }
    return BSearchRecHelper(key, base, 0, itemCount, itemSize, cmp);
}

int main(void)
{

    int nums[] = { 0, 2, 3, 5, 7, 9, 11 };
    const int NUMS_LEN = 7;
    int key = 0;
    int ind = -1;

    const int KEY_COUNT = 2000000;

    clock_t start = 0;
    clock_t end = 0;

    start = clock();
    for (int i = 0; i < KEY_COUNT; ++i) {
        key = i;
        ind = BSearch1(&key, nums, NUMS_LEN, sizeof(int), CompareInts);    
    }
    end = clock();
    printf("%d calls to BSearch with two tests in the loop took %lf seconds.\n", KEY_COUNT, (end - start) / (double)CLOCKS_PER_SEC);

    start = clock();
    for (int i = 0; i < KEY_COUNT; ++i) {
        key = i;
        ind = BSearch2(&key, nums, NUMS_LEN, sizeof(int), CompareInts);    
    }
    end = clock();
    printf("%d calls to BSearch with one test in the loop took %lf seconds.\n", KEY_COUNT, (end - start) / (double)CLOCKS_PER_SEC);

    start = clock();
    for (int i = 0; i < KEY_COUNT; ++i) {
        key = i;
        ind = BSearchRec(&key, nums, NUMS_LEN, sizeof(int), CompareInts);    
    }
    end = clock();
    printf("%d calls to recursive BSearch took %lf seconds.\n", KEY_COUNT, (end - start) / (double)CLOCKS_PER_SEC);
    
    getchar();

    return 0;
}
