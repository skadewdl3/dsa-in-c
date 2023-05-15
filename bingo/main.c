#include <stdio.h>
#include <time.h>
#include "SLL.h"

// ascii value of X is 88
#define X 88
#define _ 95
#define false 0
#define true 1

typedef enum {
  USER, COMP, NONE
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
        return 0;
      }
    }
  }
  return 1;
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
int check_bingo(SLL** rows, int dim)
{

  // i represents rows
  // j represents columns
  // in all three cases


  // rows
  for (int i = 0; i < dim; i++) {
    int cross_count = 0;
    for (int j = 0; j < dim; j++) {
      if (get(rows[i], j) == X) {
        cross_count++;
      }
    }
    if (cross_count == dim) {
      return 1;
    }
  }

  // columns
  for (int j = 0; j < dim; j++) {
    int cross_count = 0;
    for (int i = 0; i < dim; i++) {
      if (get(rows[i], j) == X) {
        cross_count++;
      }
    }
    if (cross_count == dim) {
      return 1;
    }
  }

  //diags
  // diag1 is topleft to bottomright
  // diag2 is topright to bottomleft
  int cross_count_diag1 = 0;
  int cross_count_diag2 = 0;

  for (int i = 0; i < dim; i++) {
    // check diag1 for cross
    if (get(rows[i], i) == X) {
      cross_count_diag1++;
    }

    // check diag2 for cross
    if (get(rows[i], dim - i - 1) == X) {
      cross_count_diag2++;
    }
  }

  if (cross_count_diag1 == dim || cross_count_diag2 == dim) {
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
    system("clear");
    printf("\nFill your board with numbers under 50.\n");
    print_board(rows, dim, false);
    printf("\n");
    printf("Enter number at (%d, %d): ", numbers_count / dim, numbers_count % dim);
    scanf("%d%*c", &numbers[numbers_count]);
    replace(rows[numbers_count / dim], numbers[numbers_count], numbers_count % dim);
    numbers_count++;
  }
  print_board(rows, dim, true);
  return rows;
}

SLL** create_computer_board (SLL** rows_user, int dim) {



  SLL** rows = malloc(dim * sizeof(SLL*));
  int numbers[dim * dim];
    // creating dim number of lists
  for (int i = 0; i < dim; i++) {
    rows[i] = createList();
  }
  
  // filling numbers array with 1 to dim * dum
  for (int i = 0; i < dim; i++) {
    for (int j = 0; j < dim; j++) {
      numbers[i * dim + j] = get(rows_user[i], j);
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
  SLL** rows_comp = create_computer_board(rows_user, dim);

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
  Player winner = USER;
  int called;
  int num_calls = 0;

  // game loop
  while (1) {
    system("clear");
    printf("\nYour board: \n");
    print_board(rows_user, dim, false);
    // printf("\nComputers board: \n");
    // print_board(rows_comp, dim, false);

    if (caller == USER) {
      printf("Call your number: ");
      scanf("%d%*c", &called);
      printf("\nyou called: %d", called);
      while (is_number_crossed(rows_user, dim, called)) {
        printf("Call another number: ");
        scanf("%d%*c", &called);
      }
      cross_number(rows_user, dim, called);
      cross_number(rows_comp, dim, called);
      caller = COMP;
    }

    else if (caller == COMP) {
      printf("Press enter for computer to call next number: ");
      getchar();
      called = computer_calls[num_calls];
      while (is_number_crossed(rows_comp, dim, called)) {
        num_calls++;
        called = computer_calls[num_calls];
      }
      num_calls++;
      cross_number(rows_user, dim, called);
      cross_number(rows_comp, dim, called);
      caller = USER;
    }

    int comp_bingo = check_bingo(rows_comp, dim);
    int user_bingo = check_bingo(rows_user, dim);

    if (comp_bingo && user_bingo) {
      winner = NONE;
      break;
    }
    else if (comp_bingo) {
      winner = COMP;
      break;
    }
    else if (user_bingo) {
      winner = USER;
      break;
    }
  }

  printf("\nBINGO!\n");
  if (winner == NONE) {
    system("clear");
    printf("Draw!\n\n");
    printf("Your board: \n");
    print_board(rows_user, dim, false);
    printf("Computers board: \n");
    print_board(rows_comp, dim, false);
  }
  else if (winner == USER) {
    system("clear");
    printf("You won!\n\n");
    printf("Your board: \n");
    print_board(rows_user, dim, false);
    printf("Computers board: \n");
    print_board(rows_comp, dim, false);
  }
  else if (winner == COMP) {
    system("clear");
    printf("Computer won!\n\n");
    printf("Your board: \n");
    print_board(rows_user, dim, false);
    printf("Computers board: \n");
    print_board(rows_comp, dim, false);
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

/*
if dim = 3

numbers = {1, 2 ,3, 4, 5, 6, 7, 8, 9}

for 8, row = 2, col = 1
for 8 in numbers, index = 7

1 2 3
4 5 6
7 8 9

*/