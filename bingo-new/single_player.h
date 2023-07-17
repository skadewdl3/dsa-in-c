
void singlePlayerBingo () {
  int dim;

  clear_screen();

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
    clear_screen();
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
    clear_screen();
    printf("Draw!\n\n");
    printf("Your board: \n");
    print_board(rows_user, dim, false);
    printf("Computers board: \n");
    print_board(rows_comp, dim, false);
  }
  else if (winner == USER) {
    clear_screen();
    printf("You won!\n\n");
    printf("Your board: \n");
    print_board(rows_user, dim, false);
    printf("Computers board: \n");
    print_board(rows_comp, dim, false);
  }
  else if (winner == COMP) {
    clear_screen();
    printf("Computer won!\n\n");
    printf("Your board: \n");
    print_board(rows_user, dim, false);
    printf("Computers board: \n");
    print_board(rows_comp, dim, false);
  }
}