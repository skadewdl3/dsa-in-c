#include <stdio.h>
#include <stdlib.h>

typedef struct {
  char* data;
  int size;
  int max_size;
} CharStack;

CharStack* CharStack_create () {
  CharStack* stack = (CharStack*)malloc(sizeof(CharStack));
  stack->data = malloc(sizeof(char) * 1);
  stack->size = 0;
  stack->max_size = -1;
  return stack;
}

void CharStack_destroy (CharStack* stack) {
  free(stack->data);
  free(stack);
}

void CharStack_set_max_size (CharStack* stack, int size) {
  stack->max_size = size;
  // do clipping off operation
}

int CharStack_is_empty (CharStack* stack) {
  return stack->size == 0;
}

int CharStack_is_full (CharStack* stack) {
  return stack->size == stack->max_size;
}



void CharStack_print (CharStack* stack) {
  for (int i = 0; i < stack->size; i++) {
    printf("%s%c%s ", i == 0 ? "[" : "" ,stack->data[i], i == 0 ? "]" : "");
  }
  printf("\n");
}


void CharStack_push (CharStack* stack, char element) {
  if (CharStack_is_full(stack)) {
    // print error
    return;
  }
  stack->data = realloc(stack->data, sizeof(char) * (stack->size + 1));
  stack->data[stack->size] = element;
  stack->size++;
}

char CharStack_pop (CharStack* stack) {
  if (CharStack_is_empty(stack)) {
    // print error
    return '\0';
  }
  if (stack->size == 1) {
    char deleted = stack->data[0];
    stack->size = 0;
    return deleted;
  }
  char deleted = stack->data[stack->size - 1];
  stack->data = realloc(stack->data, sizeof(char) * (stack->size - 1));
  stack->size--;
  return deleted;
}

char CharStack_peek (CharStack* stack) {
  if (CharStack_is_empty(stack)) {
    // print error
    return '\0';
  }
  return stack->data[stack->size - 1];
}
