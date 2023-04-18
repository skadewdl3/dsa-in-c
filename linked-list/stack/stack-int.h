#include <stdio.h>
#include <stdlib.h>
#include "./../singly-linked-list/singly-linked-list.h"


typedef struct StackStruct {
  IntLL *items;
  IntNode* top;
} Stack;

Stack *Stack_create () {
  Stack *st = malloc(sizeof(Stack));
  st->items = IntLL_create(); 
  st->top = st->items->head;
  return st;
}

int Stack_is_empty (Stack* st) {
  return LL_is_empty(st->items);
}

void Stack_push (Stack* st, int value) {
  LL_unshift(st->items, value);
  st->top = st->items->head;
}

int Stack_pop (Stack *st) {
  int value = LL_shift(st->items);
  st->top = st->items->head;
  return value;
}

int Stack_peek (Stack *st) {
  return st->top->value; 
}

void Stack_print (Stack *st) {
  return LL_print(st->items);
}
