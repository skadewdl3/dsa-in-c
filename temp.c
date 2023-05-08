#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "./linked-list/singly-linked-list/singly-linked-list.h"

#define ROWS 5
#define COLS 5

typedef struct {
    int number;
    int checked;
} Square;

void print_board(Square board[ROWS][COLS])
{
    printf(" B  I  N  G  O\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (board[i][j].checked) {
                printf("|X ");
            } else {
                printf("|%2d", board[i][j].number);
            }
        }
        printf("|\n");
    }
}

int check_bingo(Square board[ROWS][COLS])
{
    int rows[ROWS] = {0};
    int cols[COLS] = {0};
    int diag1 = 0;
    int diag2 = 0;

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (board[i][j].checked) {
                rows[i]++;
                cols[j]++;
                if (i == j) {
                    diag1++;
                }
                if (i + j == ROWS - 1) {
                    diag2++;
                }
            }
        }
    }

    for (int i = 0; i < ROWS; i++) {
        if (rows[i] == ROWS || cols[i] == COLS) {
            return 1;
        }
    }

    if (diag1 == ROWS || diag2 == ROWS) {
        return 1;
    }

    return 0;
}

int main()
{
    Square board[ROWS][COLS];
    int numbers[ROWS * COLS];
    int num_count = 0;
    srand(time(NULL));

    // initialize board
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            board[i][j].number = num_count + 1;
            board[i][j].checked = 0;
            num_count++;
        }
    }

    // initialize numbers array
    for (int i = 0; i < ROWS * COLS; i++) {
        numbers[i] = i + 1;
    }

    // shuffle numbers array
    for (int i = 0; i < ROWS * COLS; i++) {
        int j = rand() % (ROWS * COLS);
        int temp = numbers[i];
        numbers[i] = numbers[j];
        numbers[j] = temp;
    }

    // play game
    int num_calls = 0;
    while (!check_bingo(board)) {
        system("clear");
        printf("Number of calls: %d\n", num_calls);
        print_board(board);
        printf("Press ENTER to call next number...\n");
        getchar();
        int next_num = numbers[num_calls];
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                if (board[i][j].number == next_num) {
                    board[i][j].checked = 1;
                }
            }
        }
        num_calls++;
    }

    // game over
    system("clear");
    printf("Number of calls: %d\n", num_calls);
    print_board(board);
    printf("BINGO!!!\n");
    }