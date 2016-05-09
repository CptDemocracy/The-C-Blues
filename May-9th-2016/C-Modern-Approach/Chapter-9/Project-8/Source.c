/*
K.N.King "C Programming. A Modern Approach."
Programming project 8 p.217

Write a program that simulates the game of craps, which is played with
two dice. On the first roll, the player wins if the sum of the dice is
7 or 11. The player loses if the sum is 2, 3 or 12. Any other roll is
called the "point" and the game continues. On each subsequent roll,
the player wins if he or she rolls the point again. The player loses
by rolling 7. Any other roll is ignored and the game continues. At the
end of each game, the program will ask the user whether or not to play
again. When the user enters a response other than y or Y, the program
will display the number of wins and losses and then terminate.

"You rolled: 8
Your point is 8
You rolled: 3
You rolled: 10
You rolled: 8
You win!

Play again! y

You rolled: 6
Your point is 6
You rolled: 5
You rolled: 12
You rolled: 3
You rolled: 7
You lose!

Play again? y

You rolled: 11
You win!

Play again? n

Wins: 2 Losses: 1
"
*/

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>

int RollDiceSum(int count);

void OnWin(void);

void OnLose(void);

int OnContinue(void);

int main(void)
{
    unsigned int seed = (unsigned int)time(NULL);
    srand(seed);

    int roll = 0;
    int sum = 0;
    int diceCount = 2;

    int wins = 0;
    int losses = 0;

    int isGameOver = 0;

    while (1)
    {
        isGameOver = 0;
        roll = 0;
        
        while (!isGameOver)
        {
            sum = RollDiceSum(diceCount);

            printf("You rolled %d.\n", sum);

            if (roll == 1) {
                if (sum == 7 || sum == 11) {
                    // WIN
                    OnWin();
                    ++wins;
                    isGameOver = 1;
                } else if (sum == 2 || sum == 3 || sum == 12) {
                    // LOSS
                    OnLose();
                    ++losses;
                    isGameOver = 1;
                }
            } else if (sum == 7) {
                // LOSS
                OnLose();
                ++losses;
                isGameOver = 1;
            }

            ++roll;
        }

        char answer = '\0';
        char c = '\0';
        printf("Would you like to play again? (y/n)\n");
        while (scanf(" %c", &answer) != 1) {
            printf( "I am sorry, didn't quite get it.\n"
                    "Would you like to play again? (y/n)\n");

            while ((c = getchar()) != '\n' && c != EOF) continue;
        }
        while ((c = getchar()) != '\n' && c != EOF) continue;

        if (tolower(answer) != 'y') {
            printf("%d wins, %d losses.\n", wins, losses);
            break;
        }
    }

    getchar();
    return EXIT_SUCCESS;
}

int RollDiceSum(int count) 
{    
    const static int DIE_SIDE_POINTS[] = {
        [0] = 1,
        [1] = 2,
        [2] = 3,
        [3] = 4,
        [4] = 5,
        [5] = 6
    };
    const int DIE_SIDE_COUNT = (int)(sizeof(DIE_SIDE_POINTS) / sizeof(DIE_SIDE_POINTS[0]));

    int sum = 0;
    while (count > 0) {
        sum += DIE_SIDE_POINTS[rand() % DIE_SIDE_COUNT];
        --count;
    }
    return sum;
}

void OnWin(void) {
    printf("You win!\n");
}

void OnLose(void) {
    printf("You lose!\n");
}
