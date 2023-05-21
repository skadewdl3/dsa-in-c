#include <stdio.h>
#include "stack.h"

int main () {
  CharStack *stack = CharStack_create();
  Stack_push(stack, 'a');
  Stack_push(stack, 'b');
  Stack_push(stack, 'c');
  Stack_print(stack);
  printf("\n%c", Stack_peek(stack)) ;
}