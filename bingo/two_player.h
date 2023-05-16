void twoPlayerBingo () {

  int dim;

  printf("\nEnter size of board: ");
  scanf("%d%*c", &dim);

  Player caller;
  Player next;
  int temp;

  printf("Are you player 1 or 2? - ");
  scanf("%d", &temp);

  while (temp != 1 && temp != 2) {
    printf("Are you player 1 or 2? - ");
    scanf("%d", &temp);
  }

  if (temp == 1) {
    caller = USER1;
    next = USER2;
  }
  else {
    caller = USER2;
    next = USER1;
  }



  // creates user and computer boards
  SLL** rows_user = create_user_board(dim);



  int called;

  while (1) {
    system("clear");
    printf("\nYour board: \n");
    print_board(rows_user, dim, false);
    
    if (caller == USER1) {
      printf("Call your number: ");
      scanf("%d%*c", &called);
      printf("\nyou called: %d", called);
      while (is_number_crossed(rows_user, dim, called)) {
        printf("Call another number: ");
        scanf("%d%*c", &called);
      }
      cross_number(rows_user, dim, called);
      caller = USER2;
    }
    else if (caller == USER2) {
      
      printf("Enter called number: ");
      scanf("%d%*c", &called);
      printf("\ncalled number is: %d", called);
      cross_number(rows_user, dim, called);
      caller = USER1;
    }

    int user_bingo = check_bingo(rows_user, dim);

    if (user_bingo) {
      break;
    }
  }

  system("clear");
  printf("\nBINGO!\n");
  printf("You win!\n\n");
  printf("Your board: \n");
  print_board(rows_user, dim, false);
}