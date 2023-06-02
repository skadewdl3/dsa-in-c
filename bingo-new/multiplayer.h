
void multiPlayerBingo () {
  int dim;

  clear_screen();

  printf("\nEnter size of board(Greater than or equal to 5): ");
  scanf("%d%*c", &dim);

while(dim<5)
{
  multiPlayerBingo();
}

  // creates user and computer boards
  SLL** rows_user = create_user_board(dim);
  SLL** rows_comp1 = create_computer_board(rows_user, dim);
  SLL** rows_comp2 = create_computer_board(rows_comp1, dim);
  SLL** rows_comp3 = create_computer_board(rows_comp2, dim);

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
  int num_calls1 = 0;
  int num_calls2 = 0;
  int num_calls3 = 0;

  // game loop
  while (1) {
    clear_screen();
    printf("\nYour board: \n");
    print_board(rows_user, dim, false);
    printf("\nComputers boards1: \n");
    print_board(rows_comp1, dim, false);
    printf("\nComputers boards2: \n");
    print_board(rows_comp2, dim, false);
    printf("\nComputers boards3: \n");
    print_board(rows_comp3, dim, false);

    if (caller == USER) {
      printf("Call your number: ");
      scanf("%d%*c", &called);
      printf("\nyou called: %d", called);
      while (is_number_crossed(rows_user, dim, called)) {
        printf("Call another number: ");
        scanf("%d%*c", &called);
      }
      cross_number(rows_user, dim, called);
      cross_number(rows_comp1, dim, called);
      cross_number(rows_comp2, dim, called);
      cross_number(rows_comp3, dim, called);
      caller = COMP1;
    }

    else if (caller == COMP1) {
      printf("Press enter for computer to call next number: ");
      getchar();
      called = computer_calls[num_calls1];
      while (is_number_crossed(rows_comp1, dim, called)) {
        num_calls1++;
        called = computer_calls[num_calls1];
        caller = COMP2;
      }
      num_calls1++;
    }
    else if (caller == COMP2) {

      printf("Press enter for computer to call next number: ");
      while (is_number_crossed(rows_comp2, dim, called)) {
        num_calls2++;
        called = computer_calls[num_calls2];
        caller = COMP3;
      }
      num_calls2++;
    }
    else if (caller == COMP3) {

      printf("Press enter for computer to call next number: ");
      while (is_number_crossed(rows_comp3, dim, called)) {
        num_calls3++;
        called = computer_calls[num_calls3];
        caller = USER;
      }
      num_calls3++;
    }
      cross_number(rows_user, dim, called);
      cross_number(rows_comp1, dim, called);
      cross_number(rows_comp2, dim, called);
      cross_number(rows_comp3, dim, called);

    int comp_bingo1 = check_bingo(rows_comp1, dim);
    int comp_bingo2 = check_bingo(rows_comp2, dim);
    int comp_bingo3 = check_bingo(rows_comp3, dim);
    int user_bingo = check_bingo(rows_user, dim);

    if (comp_bingo1 && comp_bingo2 && comp_bingo3 && user_bingo) {
      winner = NONE;
      break;
    }
    else if (comp_bingo1 ) {
      winner = COMP1;
      break;
    }
    else if ( comp_bingo2 ) {
      winner = COMP2;
      break;
    }
    else if ( comp_bingo3) {
      winner = COMP3;
      break;
    }
    else if (user_bingo) {
      winner = USER;
      break;
    }
  }

  printf("\nBINGO!\n");
  if (winner == NONE) {
    clear_screen();
    printf("Draw!\n\n");
    printf("Your board: \n");
    print_board(rows_user, dim, false);
    printf("Computers board: \n");
    print_board(rows_comp1, dim, false);
    print_board(rows_comp2, dim, false);
    print_board(rows_comp3, dim, false);
  }
  else if (winner == USER) {
    clear_screen();
    printf("You won!\n\n");
    printf("Your board: \n");
    print_board(rows_user, dim, false);
    printf("Computers board: \n");
    print_board(rows_comp1, dim, false);
    print_board(rows_comp2, dim, false);
    print_board(rows_comp3, dim, false);
  }
  else if (winner == COMP1) {
    clear_screen();
    printf("Computer won!\n\n");
    printf("Your board: \n");
    print_board(rows_user, dim, false);
    printf("Computers board1: \n");
    print_board(rows_comp1, dim, false);
  }
  else if (winner == COMP2) {
    clear_screen();
    printf("Computer won!\n\n");
    printf("Your board: \n");
    print_board(rows_user, dim, false);
    printf("Computers board2: \n");
    print_board(rows_comp2, dim, false);
  }
  else if (winner == COMP3) {
    clear_screen();
    printf("Computer won!\n\n");
    printf("Your board: \n");
    print_board(rows_user, dim, false);
    printf("Computers board3: \n");
    print_board(rows_comp3, dim, false);
  }
}