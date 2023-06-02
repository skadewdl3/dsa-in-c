#include "./LLStack.h"
#define BLUE "\e[0;36m"
#define RESET "\x1b[m"

int disk_count = 0;
Stack* source = NULL;
Stack* auxiliary = NULL;
Stack* destination = NULL;

void print_rods () {
  
  int print_source = 0;
  int print_dest = 0;
  int print_aux = 0;
  printf("\n");
  for (int i = 0; i < disk_count; i++) {
    printf("\n");
    if (Stack_size(source) == disk_count - i) {
      print_source = 1;
    }
    if (Stack_size(auxiliary) == disk_count - i) {
      print_aux = 1;
    }
    if (Stack_size(destination) == disk_count - i) {
      print_dest = 1;
    }
    if (print_source) {
      printf("%d ", Stack_get(source, source->items->length - (disk_count - i)));
    } else {
      printf("  ");
    }
    if (print_aux) {
      printf("%d ", Stack_get(auxiliary, auxiliary->items->length - (disk_count - i)));
    } else {
      printf("  ");
    }
    if (print_dest) {
      printf("%d ", Stack_get(destination, destination->items->length - (disk_count - i)));
    } else {
      printf("  ");
    }
  }
    printf(BLUE "\n%c %c %c" RESET, source->name, auxiliary->name, destination->name);

}

void tower_of_hanoi (int disk_count, Stack* source, Stack* auxiliary, Stack* destination) {

  if (disk_count == 1) {
    Stack_push(destination, Stack_pop(source));
    print_rods();
    printf("\nMove disk 1 from rod %c to rod %c.", source->name, destination->name);
    return;
  }
  tower_of_hanoi(disk_count - 1, source, destination, auxiliary);
  Stack_push(destination, Stack_pop(source));
  print_rods();
  printf("\nMove disk %d from rod %c to rod %c.", disk_count, source->name, destination->name);
  tower_of_hanoi(disk_count - 1, auxiliary, source, destination);

}

int main () {

  disk_count = 4;

  source = Stack_create('A');
  auxiliary = Stack_create('B');
  destination = Stack_create('C');


  for (int i = disk_count; i >= 1; i--) {
    Stack_push(source, i);
  }

  print_rods();
  printf("\nStart condition");

  tower_of_hanoi(disk_count, source, auxiliary, destination);
  return 0;
}