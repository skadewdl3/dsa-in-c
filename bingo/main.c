#include <stdio.h>
#include <time.h>
#include "SLL.h"

// ascii value of X is 88
#define X 88
#define _ 95
#define false 0
#define true 1

typedef enum {
  USER, COMP
} Player;

// prints the board
void print_board (SLL** rows, int length, int clear_screen) {
  if (clear_screen) system("clear");
  for (int i = 0; i < length; i++) {
    print_list(rows[i]);
  }
}

// checks whether that position is crossed out or not
int is_crossed (SLL** rows, int length, int row, int col) {  
  return get(rows[row], col) == X;
}

int is_number_crossed (SLL** rows, int length, int number) {
  for (int i = 0; i < length; i++) {
    for (int j = 0; j < length; j++) {
      if (get(rows[i], j) == number) {
        return 1;
      }
    }
  }
  return 0;
}

void cross_number (SLL** row, int length, int number) {
  for (int i = 0; i < length; i++) {
    for (int j = 0; j < length; j++) {
      if (get(row[i], j) == number) {
        replace(row[i], X, j);
      }
    }
  }
}

// checks whether the board is a bingo or not
int check_bingo(SLL** rowData, int dim)
{

    int rows[dim];
    int cols[dim];

    for (int i = 0; i < dim; i++) {
        rows[i] = 0;
        cols[i] = 0;
    }

    int diag1 = 0;
    int diag2 = 0;

    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            if (is_crossed(rowData, dim, i, j)) {
                rows[i]++;
                cols[j]++;
                if (i == j) {
                    diag1++;
                }
                if (i + j == dim - 1) {
                    diag2++;
                }
            }
        }
    }

    for (int i = 0; i < dim; i++) {
        if (rows[i] == dim || cols[i] == dim) {
            return 1;
        }
    }

    if (diag1 == dim || diag2 == dim) {
        return 1;
    }

    return 0;
}

SLL** create_user_board (int dim) {
  SLL** rows = malloc(dim * sizeof(SLL*));
  int numbers[dim * dim];
  int numbers_count = 0;
    // creating dim number of lists
  for (int i = 0; i < dim; i++) {
    rows[i] = createList();
    for (int j = 0; j < dim; j++) {
      insertAtEnd(rows[i], _);
    }
  }
  
  // get values of inputs from user
  while (numbers_count < dim * dim) {
    print_board(rows, dim, true);
    printf("Enter number at: (%d, %d)", numbers_count / dim, numbers_count % dim);
    scanf("%d%*c", &numbers[numbers_count]);
    replace(rows[numbers_count / dim], numbers[numbers_count], numbers_count % dim);
    numbers_count++;
  }
  print_board(rows, dim, true);
  return rows;
}

SLL** create_computer_board (int dim) {
  SLL** rows = malloc(dim * sizeof(SLL*));
  int numbers[dim * dim];
    // creating dim number of lists
  for (int i = 0; i < dim; i++) {
    rows[i] = createList();
  }
  // filling numbers array with 1 to dim * dum
  for (int i = 0; i < dim; i++) {
    for (int j = 0; j < dim; j++) {
      numbers[i * dim + j] = i * dim + j + 1;
    }
  }

  // randomising values in numbers array
  srand(time(NULL));
  for (int i = 0; i < dim * dim; i++) {
    int j = rand() % (dim * dim);
    int temp = numbers[i];
    numbers[i] = numbers[j];
    numbers[j] = temp;
  }

  // filling board with values from numbers array
  for (int i = 0; i < dim; i++) {
    for (int j = 0; j < dim; j++) {
      insertAtEnd(rows[i], numbers[i * dim + j]);
    }
  }
  return rows;
}

int* randomise (int* arr, int length) {
  srand(time(NULL));
  for (int i = 0; i < length; i++) {
    int j = rand() % (length);
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
  }
  return arr;
}

int main () {

  // rule: numbers between 1 and dim*dim only.

  // before presenting, set dim = 5
  int dim;
  printf("\nEnter size of board: ");
  scanf("%d%*c", &dim);

  // creates user and computer boards
  SLL** rows_user = create_user_board(dim);
  SLL** rows_comp = create_computer_board(dim);

  // randomises computer calls
  int* computer_calls = (int*)malloc(dim * dim * sizeof(int));
  for (int i = 0; i < dim * dim; i++) {
    computer_calls[i] = i + 1;
  }
  computer_calls = randomise(computer_calls, dim * dim);
  

  for (int i = 0; i < dim * dim; i++) {
    printf("%d ", computer_calls[i]);
  }

  // user calls a number first
  Player caller = USER;
  int called;
  int num_calls = 0;

  // game loop
  while (!check_bingo(rows_comp, dim) && !check_bingo(rows_user, dim)) {
    printf("\nYour board: \n");
    print_board(rows_user, dim, true);
    printf("\nComputers board: \n");
    print_board(rows_comp, dim, false);

    if (caller == USER) {
      printf("Call your number: ");
      scanf("%d%*c", &called);
      while (is_number_crossed(rows_user, dim * dim, called)) {
        num_calls++;
        printf("Call another number: ");
        scanf("%d%*c", &called);
      }
      cross_number(rows_user, dim, called);
      cross_number(rows_comp, dim, called);
      caller = COMP;
    }

    else if (caller = COMP) {
      printf("Press enter for computer to call next number: ");
      getchar();
      called = computer_calls[num_calls];
      while (is_number_crossed(rows_comp, dim * dim, called)) {
        num_calls++;
        called = computer_calls[num_calls];
      }
      num_calls++;
      cross_number(rows_user, dim, called);
      cross_number(rows_comp, dim, called);
      caller = USER;
    }
  }

  


  // shuffling the numbers to be called
  


  // int num_calls = 0;
  // while (check_bingo(rows, dim) != 1) {
  //   system("clear");
  //   print_board(rows, dim);
  //   printf("\nPress enter to call a number: ");
  //   getchar();
  //   int called = numbers[num_calls];

  //   for (int i = 0; i < dim; i++) {
  //     for (int j = 0; j < dim; j++) {
  //       if (get(rows[i], j) == called) {
  //         replace(rows[i], 'X', j);
  //       }
  //     }
  //   }

  //   num_calls++;
  // }
  // print_board(rows_comp, dim);
}


/*
if dim = 3

numbers = {1, 2 ,3, 4, 5, 6, 7, 8, 9}

for 8, row = 2, col = 1
for 8 in numbers, index = 7

1 2 3
4 5 6
7 8 9

*/