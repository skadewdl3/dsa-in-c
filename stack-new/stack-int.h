#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int* data;
  int size;
  int max_size;
} IntStack;

IntStack* IntStack_create () {
  IntStack* stack = (IntStack*)malloc(sizeof(IntStack));
  stack->data = malloc(sizeof(int) * 1);
  stack->size = 0;
  stack->max_size = -1;
  return stack;
}

void IntStack_destroy (IntStack* stack) {
  free(stack->data);
  free(stack);
}

void IntStack_set_max_size (IntStack* stack, int size) {
  stack->max_size = size;
  // do clipping off operation
}

int IntStack_is_empty (IntStack* stack) {
  return stack->size == 0;
}

int IntStack_is_full (IntStack* stack) {
  return stack->size == stack->max_size;
}


void IntStack_push (IntStack* stack, int element) {
  if (IntStack_is_full(stack)) {
    // print error
    return;
  }
  stack->data = realloc(stack->data, sizeof(int) * (stack->size + 1));
  stack->data[stack->size] = element;
  stack->size++;
}

int IntStack_pop (IntStack* stack) {
  if (IntStack_is_empty(stack)) {
    // print error
    return -1;
  }
  stack->data = realloc(stack->data, sizeof(int) * (stack->size - 1));
  int deleted = stack->data[stack->size - 1];
  stack->size--;
  return deleted;
}

int IntStack_peek (IntStack* stack) {
  if (IntStack_is_empty(stack)) {
    // print error
    return -1;
  }
  return stack->data[stack->size - 1];
}

void IntStack_print (IntStack* stack) {
  for (int i = 0; i < stack->size; i++) {
    printf("%s%d%s ", i == 0 ? "[" : "" ,stack->data[i], i == 0 ? "]" : "");
  }
  printf("\n");
}