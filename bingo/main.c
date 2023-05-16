#include <stdio.h>
#include <time.h>
#include "SLL.h"
#include "common.h"
#include "single_player.h"
#include "two_player.h"

int main () {

  int mode;

  printf("\nEnter game mode:\n");
  printf("1. Single player (vs computer)\n");
  printf("2. Two player\n");
  printf("3. Exit\n");
  
  scanf("%d%*c", &mode);
  
  switch (mode) {
    case 1:
      printf("\nSingle player mode selected.\n");
      singlePlayerBingo();
      break;
    case 2:
      printf("\nTwo player mode selected.\n");
      twoPlayerBingo();
      break;
    default:
      printf("\nExiting...\n");
      exit(0);
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