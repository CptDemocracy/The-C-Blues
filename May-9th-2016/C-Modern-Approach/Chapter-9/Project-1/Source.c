/*
K.N.King "C Programming. A Modern Approach."
Programming project 1 p.217

Write a program that asks the user to enter a series 
of integers (which it stores in an array), then sorts
it recursively using selection sort.

*/

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

// This algorithm is so slow cpu cycles go
// in reverse when you execute it
int SelectionSortRecursive(int* nums, int numsSize);

int SelectionSortRecursiveHelper(int* nums, int numsSize);

int main(void)
{
    printf( "Please enter a series of integers you would like sorted\n"
            "using one of the slowest sorting algorithm in the world\n"
            " - selection sort:\n");

    int numsCapacity = 4;
    int* nums = (int*)calloc(numsCapacity, sizeof(int));
    if (!nums) {
        return EXIT_FAILURE;
    }
    int numsCount = 0;

    char c = '\0';

    while (1)
    {
        while (scanf("%d", &nums[numsCount]) != 1) {
            memset(nums, 0, numsCount * sizeof(int));
            numsCount = 0;

            fprintf(stderr, "Input invalid. Please try re-entering "
                            "the number of integers again.\n");

            while ((c = getchar()) != '\n' && c != EOF) continue;
        }

        ++numsCount;

        if (numsCount >= numsCapacity) {
            int newCapacity = numsCapacity * 2;
            int* newNums = (int*)calloc(newCapacity, sizeof(int));
            if (!newNums) {
                return EXIT_FAILURE;
            }
            memcpy(newNums, nums, numsCount * sizeof(int));
            free(nums);
            nums = NULL;

            nums = newNums;
            numsCapacity = newCapacity;
        }        

        while ((c = getchar()) != '\n') {
            if (!isspace(c)) {
                ungetc(c, stdin);
                break;
            }
        }
        if (c == '\n') break;
    }

    (void) SelectionSortRecursive(nums, numsCount);

    for (int i = 0; i < numsCount; ++i) printf("%d ", nums[i]);
    putchar('\n');

    free(nums);

    getchar();
    return EXIT_SUCCESS;
}

int SelectionSortRecursive(int* nums, int numsSize) {
    if (!nums) {
        return 1;
    }
    if (numsSize < 0) {
        return 2;
    }
    return SelectionSortRecursiveHelper(nums, numsSize);
}

int SelectionSortRecursiveHelper(int* nums, int numsSize) {
    if (numsSize < 2) {
        return 0;
    }
    int minAtIndex = 0;
    int i = 0;
    while (i < numsSize) {
        if (nums[i] < nums[minAtIndex]) minAtIndex = i;
        ++i;
    }
    int temp = nums[0];
    nums[0] = nums[minAtIndex];
    nums[minAtIndex] = temp;

    return SelectionSortRecursiveHelper(nums + 1, numsSize - 1);
}
