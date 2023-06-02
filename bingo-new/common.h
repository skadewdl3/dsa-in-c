// ascii value of X is 88
// ascii value of _ is 95
#define X 88
#define _ 95
#define false 0
#define true 1

typedef enum {
  USER, COMP, COMP1,COMP2,COMP3, NONE, USER1, USER2
  /*
  int USER = 0
  int COMP = 1
  int NONE = 2

  */
} Player;

void clear_screen () {
  printf("\033[2J\033[1;1H");
}

// prints the board
void print_board (SLL** rows, int length, int cls) {
  if (cls) clear_screen();
  for (int i = 0; i < length; i++) {
    print_list(rows[i]);
    /*
    print_list([_, _, _..])

    */
  }
}

// checks whether that position is crossed out or not
int is_crossed (SLL** rows, int length, int row, int col) {  
  return get(rows[row], col) == X;
}

int is_number_existing (SLL** rows, int length, int number) {
  for (int i = 0; i < length; i++) {
    for (int j = 0; j < length; j++) {
      if (get(rows[i], j) == number) {
        return 1;
      }
    }
  }
  return 0;
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
  int line_count = 0;

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
      line_count ++ ;
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
      line_count ++;
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
    line_count ++;
  }
if(line_count == dim)
{
  return 1;
}
else
{
  return 0;
}

}

SLL** create_user_board (int dim) {
  SLL** rows = malloc(dim * sizeof(SLL*));
  /*
  {
    [_, _, ...],
    ...
  }
  */
  int numbers[dim * dim];
  int numbers_count = 0;

    // creating dim number of lists
  for (int i = 0; i < dim; i++) {
    rows[i] = createList();
    // rows[0] =  createList()
    // SLL*
    for (int j = 0; j < dim; j++) {
      insertAtEnd(rows[i], _);
    }
  }
  
  // get values of inputs from user
  while (numbers_count < dim * dim) {
    clear_screen();
    printf("\nFill your board with numbers under 50.\n");
    print_board(rows, dim, false);
    printf("\n");
    printf("Enter number at (%d, %d): ", numbers_count / dim, numbers_count % dim);
    scanf("%d%*c", &numbers[numbers_count]);
    while (is_number_existing(rows, dim, numbers[numbers_count])) {
      printf("Enter another number at (%d, %d): ", numbers_count / dim, numbers_count % dim);
      scanf("%d%*c", &numbers[numbers_count]);
    }
    replace(rows[numbers_count / dim], numbers[numbers_count], numbers_count % dim);
    numbers_count++;

  }
  print_board(rows, dim, true);
  return rows;
}

SLL** create_computer_board (SLL** rows_user, int dim) {

/*
{
  [1, 2, 3, 4, 100],
  ...
}
*/

/*
{
  [1, 2, 3, 4, 100] 
}
*/


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
  numbers = randomise(numbers, dim * dim);

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
