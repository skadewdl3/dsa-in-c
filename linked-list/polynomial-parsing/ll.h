#include <stdio.h>
#include <stdlib.h>
#include "./ll-errors.h"

typedef struct Poly {
  int coefficient;
  int exponent;
} Polynomial;

typedef struct IntLLNode
{
  Polynomial value;
  struct IntLLNode *next;
} IntNode;

typedef struct
{
  int length;
  IntNode *head;
} IntLL;

Polynomial Polynomial_create (int coefficient, int exponent) {
  Polynomial p;
  p.coefficient = coefficient;
  p.exponent = exponent;
  return p;
}

IntNode *IntNode_create(Polynomial p)
{
  IntNode *v = (IntNode *)malloc(sizeof(IntNode));
  if (v == NULL) {
    LL_error(MEM_ALLOC_ERROR);
    exit(1);
  }
  v->next = NULL;
  v->value = p;
  return v;
}

void IntNode_destroy(IntNode *node)
{
  free(node);
}

IntLL *IntLL_create()
{
  IntLL *list = (IntLL*)malloc(sizeof(IntLL));
  IntNode *head = IntNode_create(Polynomial_create(0, 0));
  list->head = head;
  list->length = 0;
  return list;
}

void IntLL_destroy(IntLL *list)
{
  if (list->head == NULL) {
    LL_error(LIST_DESTROYED);
    exit(1);
  }
  IntNode *prev = NULL;
  IntNode *current = list->head;
  while (current->next != NULL)
  {
    prev = current;
    current = current->next;
    IntNode_destroy(prev);
  }
  IntNode_destroy(current);
  free(list);
  list->head = NULL;
}

int IntLL_is_empty(IntLL *list)
{
  if (list->head == NULL) {
    LL_error(LIST_DESTROYED);
    exit(1);
  }
  return list->length == 0;
}

IntNode *IntLL_push(IntLL *list, Polynomial p)
{
  if (list->head == NULL) {
    LL_error(LIST_DESTROYED);
    exit(1);
  }
  IntNode *new_node = IntNode_create(p);
  if (IntLL_is_empty(list))
  {
    list->head = new_node;
  }
  else
  {
    IntNode *current = list->head;
    while (current->next != NULL)
    {
      current = current->next;
    }
    current->next = new_node;
  }
  list->length++;
  return new_node;
}

IntNode *IntLL_unshift(IntLL *list, Polynomial p)
{
  if (list->head == NULL) {
    LL_error(LIST_DESTROYED);
    exit(1);
  }
  IntNode *new_node = IntNode_create(p);
  if (list->length != 0) {
    new_node->next = list->head;
  }
  list->head = new_node;
  list->length++;
  return new_node;
}

Polynomial IntLL_pop(IntLL *list)
{
  if (list->head == NULL) {
    LL_error(LIST_DESTROYED);
    exit(1);
  }
  if (IntLL_is_empty(list)) {
    LL_error(LIST_EMPTY);
    return list->head->value;
  }
  IntNode *current = list->head;
  int length = list->length;
  while (length - 2)
  {
    current = current->next;
    length--;
  }
  Polynomial p = current->next->value;
  IntNode_destroy(current->next);
  current->next = NULL;
  list->length--;
  return p;
}

Polynomial IntLL_shift(IntLL *list)
{
  if (list->head == NULL) {
    LL_error(LIST_DESTROYED);
    exit(1);
  }
  if (IntLL_is_empty(list)) {
    LL_error(LIST_EMPTY);
    return list->head->value;
  }
  if (list->length == 1) {
    list->length = 0;
    return list->head->value;
  }
  IntNode *new_node_head = list->head->next;
  Polynomial p = list->head->value;
  IntNode_destroy(list->head);
  list->head = new_node_head;
  list->length--;
  return p;
}

void IntLL_print(IntLL *list)
{
  if (list->head == NULL) {
    LL_error(LIST_DESTROYED);
    exit(1);
  }
  if (list->length == 0) {
    LL_error(PRINT_EMPTY_LIST);
  }
  else {
    IntNode *current = list->head;
    while (current != NULL)
    {
      printf("\n%d", current->value);
      current = current->next;
    }
  }
  printf("\n");
}

IntLL *IntLL_insert(IntLL *list, Polynomial p, int index)
{
  if (list->head == NULL) {
    LL_error(LIST_DESTROYED);
    exit(1);
  }
  IntNode *new_node = IntNode_create(p);
  if (IntLL_is_empty(list))
  {
    list->head = new_node;
  }
  if (index < 0 || index > list->length) {
    LL_error(OUT_OF_BOUNDS);
    return list;
  }
  else
  {
    IntNode *current = list->head;
    int length = list->length;
    if (index > 0)
    {

      while (index - 1)
      {
        current = current->next;
        index--;
      }
      IntNode *old = current->next;
      new_node->next = old;
      current->next = new_node;
    }
    else
    {
      new_node->next = current;
      list->head = new_node;
    }
  }
  list->length++;
  return list;
}

IntLL *IntLL_delete(IntLL *list, int index)
{
  if (list->head == NULL) {
    LL_error(LIST_DESTROYED);
    exit(1);
  }
  if (IntLL_is_empty(list))
  {
    LL_error(LIST_EMPTY);
    return list;
  }
  if (index < 0 || index > list->length - 1) {
    LL_error(OUT_OF_BOUNDS);
    return list;
  }
  else
  {
    IntNode *current = list->head;
    if (index > 0)
    {

      while (index - 1)
      {
        current = current->next;
        index--;
      }

      IntNode *to_delete = current->next;
      current->next = to_delete->next;
      IntNode_destroy(to_delete);
    }
    else
    {
      list->head = current->next;
      IntNode_destroy(current);
    }
  }
  list->length--;
  return list;
}

IntLL *IntLL_reverse(IntLL *list)
{
  if (list->head == NULL) {
    LL_error(LIST_DESTROYED);
    exit(1);
  }
  IntNode *prev = NULL;
  IntNode *current = list->head;

  while (current->next != NULL)
  {
    IntNode *next_copy = current->next;
    IntNode *current_copy = current;
    current->next = prev;
    current = next_copy;
    prev = current_copy;
  }
  current->next = prev;
  list->head = current;
  return list;
}

Polynomial IntLL_get (IntLL *list, int index) {
  if (list->head == NULL) {
    LL_error(LIST_DESTROYED);
    exit(1);
  }
  if (IntLL_is_empty(list)) {
    LL_error(LIST_EMPTY);
    return list->head->value;
  }
  if (index < 0 || index > list->length - 1) {
    LL_error(OUT_OF_BOUNDS);
    return list->head->value;
  }

  IntNode* current = list->head;

  while (index) {
    current = current->next;
    index--;
  }

  return current->value;
}

IntLL *IntLL_set(IntLL *list, Polynomial p, int index) {
  if (list->head == NULL) {
    LL_error(LIST_DESTROYED);
    exit(1);
  }
  if (IntLL_is_empty(list)) return list;
  if (index < 0 || index > list->length - 1) {
    LL_error(OUT_OF_BOUNDS);
    return list;
  }

  IntNode* current = list->head;

  while (index) {
    current = current->next;
    index--;
  }

  current->value = p;
  return list;
}