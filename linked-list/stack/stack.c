#include <stdio.h>
#include "./stack-int.h"

int main () {

  Stack *st = Stack_create();
  Stack_push(st, 10);
  Stack_push(st, 69);
  Stack_print(st);
  Stack_pop(st);
  Stack_print(st);
  Stack_pop(st);
  Stack_print(st);
}