/*
K.N.King "C Programming. A Modern Approach."
Programming project 10 p.96

Using the switch statement, write a program that
converts a numerical grade into a letter grade:

"Enter numerical grade: 84
Letter grade: B
"

Use the following grading scale:
A = 90-100
B = 80-89
C = 70-79
D = 60-69
F = 0-59

Print an error message if the grade is larger 
than 100 or less than 0.
*/

#include <stdlib.h>
#include <stdio.h>

#define MAX_GRADE 100

/*
There's really no point in using a switch statement,
we can get away with an array and O(1) lookup based
on the grade's digit, a-la hash table.
*/

int main(void) 
{
    const char GRADES[] = {
        [0] = 'F',
        [1] = 'F',
        [2] = 'F',
        [3] = 'F',
        [4] = 'F',
        [5] = 'F',
        [6] = 'D',
        [7] = 'C',
        [8] = 'B',
        [9] = 'A',
        [10] = 'A'
    };

    int grade = 0;
    char c = '\0';

    while (1)
    {
        printf("Enter numerical grade: ");
        if (scanf("%d", &grade) != 1) {
            puts("Input invalid. Please try again.");            
            
            while ( (c = getchar()) != '\n' && c != EOF) continue;
            continue;
        }
        while ( (c = getchar()) != '\n' && c != EOF) continue;

        if (grade < 0) {
            puts("Input invalid. Grade cannot be negative. Please try again.");
            continue;
        }
        if (grade > MAX_GRADE) {
            printf("Input invalid. Grade cannot exceed %d. Please try again.\n", MAX_GRADE);
            continue;
        }
        break;
    }
    char letterGrade = GRADES[grade / 10];
    printf("Letter grade: %c\n", letterGrade);
    putchar('\n');
    getchar();
    return EXIT_SUCCESS;
}
