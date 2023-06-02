#include <stdio.h>
#include <time.h>
#include "SLL.h"
#include "common.h"
#include "single_player.h"
#include "two_player.h"
#include "multiplayer.h"

int main () {

  int mode;

  printf("\nEnter game mode:\n");
  printf("1. Single player (vs computer)\n");
  printf("2. Two player\n");
  printf("3. Multi player (vs computer)\n");
  printf("4. Exit\n");
  
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
    case 3:
      printf("\nMulti player mode selected.\n");
      multiPlayerBingo();
      break;
    default:
      printf("\nExiting...\n");
      exit(0);
  }

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