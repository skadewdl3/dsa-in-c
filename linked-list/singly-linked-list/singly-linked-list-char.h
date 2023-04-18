#include <stdio.h>
#include <stdlib.h>

typedef struct CharLLNode
{
  char value;
  struct CharLLNode *next;
} CharNode;

typedef struct
{
  int length;
  CharNode *head;
} CharLL;

CharNode *CharNode_create(int val)
{
  CharNode *v = (CharNode *)malloc(sizeof(CharNode));
  if (v == NULL) {
    LL_error(MEM_ALLOC_ERROR);
    exit(1);
  }
  v->next = NULL;
  v->value = val;
  return v;
}

void CharNode_destroy(CharNode *node)
{
  
  free(node);
}

CharLL *CharLL_create()
{
  CharLL *list = (CharLL*)malloc(sizeof(CharLL));
  CharNode *head = CharNode_create(0);
  list->head = head;
  list->length = 0;
  return list;
}

void CharLL_destroy(CharLL *list)
{
  if (list->head == NULL) {
    LL_error(LIST_DESTROYED);
    exit(1);
  }
  CharNode *prev = NULL;
  CharNode *current = list->head;
  while (current->next != NULL)
  {
    prev = current;
    current = current->next;
    CharNode_destroy(prev);
  }
  CharNode_destroy(current);
  free(list);
  list->head = NULL;
}

int CharLL_is_empty(CharLL *list)
{
  if (list->head == NULL) {
    LL_error(LIST_DESTROYED);
    exit(1);
  }
  return list->length == 0;
}

CharLL *CharLL_push(CharLL *list, char value)
{
  if (list->head == NULL) {
    LL_error(LIST_DESTROYED);
    exit(1);
  }
  CharNode *new_node = CharNode_create(value);
  if (CharLL_is_empty(list))
  {
    list->head = new_node;
  }
  else
  {
    CharNode *current = list->head;
    while (current->next != NULL)
    {
      current = current->next;
    }
    current->next = new_node;
  }
  list->length++;
  return list;
}

CharLL *CharLL_unshift(CharLL *list, char value)
{
  if (list->head == NULL) {
    LL_error(LIST_DESTROYED);
    exit(1);
  }
  CharNode *new_node = CharNode_create(value);
  if (list->length != 0) {
    new_node->next = list->head;
  }
  list->head = new_node;
  list->length++;
  return list;
}

CharLL *CharLL_pop(CharLL *list)
{
  if (list->head == NULL) {
    LL_error(LIST_DESTROYED);
    exit(1);
  }
  if (CharLL_is_empty(list)) {
    LL_error(LIST_EMPTY);
    return list;
  }
  CharNode *current = list->head;
  int length = list->length;
  while (length - 2)
  {
    current = current->next;
    length--;
  }
  CharNode_destroy(current->next);
  current->next = NULL;
  list->length--;
  return list;
}

CharLL *CharLL_shift(CharLL *list)
{
  if (list->head == NULL) {
    LL_error(LIST_DESTROYED);
    exit(1);
  }
  if (CharLL_is_empty(list)) {
    LL_error(LIST_EMPTY);
    return list;
  }
  CharNode *new_node_head = list->head->next;
  CharNode_destroy(list->head);
  list->head = new_node_head;
  list->length--;
  return list;
}

void CharLL_print(CharLL *list)
{
  if (list->head == NULL) {
    LL_error(LIST_DESTROYED);
    exit(1);
  }
  if (list->length == 0) {
    LL_error(PRINT_EMPTY_LIST);
  } 
  CharNode *current = list->head;
  while (current != NULL)
  {
    printf("\n%c", current->value);
    current = current->next;
  }
  printf("\n");
}

CharLL *CharLL_insert(CharLL *list, char value, int index)
{
  if (list->head == NULL) {
    LL_error(LIST_DESTROYED);
    exit(1);
  }
  CharNode *new_node = CharNode_create(value);
  if (index < 0 || index > list->length) {
    LL_error(OUT_OF_BOUNDS);
    return list;
  }
  if (CharLL_is_empty(list))
  {
    list->head = new_node;
  }
  else
  {
    CharNode *current = list->head;
    int length = list->length;
    if (index > 0)
    {

      while (index - 1)
      {
        current = current->next;
        index--;
      }
      CharNode *old = current->next;
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

CharLL *CharLL_delete(CharLL *list, int index)
{
  if (list->head == NULL) {
    LL_error(LIST_DESTROYED);
    exit(1);
  }
  if (CharLL_is_empty(list))
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
    CharNode *current = list->head;
    if (index > 0)
    {

      while (index - 1)
      {
        current = current->next;
        index--;
      }

      CharNode *to_delete = current->next;
      current->next = to_delete->next;
      CharNode_destroy(to_delete);
    }
    else
    {
      list->head = current->next;
      CharNode_destroy(current);
    }
  }
  list->length--;
  return list;
}

CharLL *CharLL_reverse(CharLL *list)
{
  if (list->head == NULL) {
    LL_error(LIST_DESTROYED);
    exit(1);
  }
  CharNode *prev = NULL;
  CharNode *current = list->head;

  while (current->next != NULL)
  {
    CharNode *next_copy = current->next;
    CharNode *current_copy = current;
    current->next = prev;
    current = next_copy;
    prev = current_copy;
  }
  current->next = prev;
  list->head = current;
  return list;
}


char CharLL_get (CharLL *list, int index) {
  if (list->head == NULL) {
    LL_error(LIST_DESTROYED);
    exit(1);
  }
  if (CharLL_is_empty(list)) {
    LL_error(LIST_EMPTY);
    return '\0';
  }
  if (index < 0 || index > list->length - 1) {
    LL_error(OUT_OF_BOUNDS);
    return '\0';
  }

  CharNode* current = list->head;

  while (index) {
    current = current->next;
    index--;
  }

  return current->value;
}

CharLL *CharLL_set(CharLL *list, char value, int index) {
  if (list->head == NULL) {
    LL_error(LIST_DESTROYED);
    exit(1);
  }
    if (CharLL_is_empty(list)) {
      LL_error(LIST_EMPTY);
      return list;
    }
  if (index < 0 || index > list->length - 1) {
    LL_error(OUT_OF_BOUNDS);
    return list;
  }

  CharNode* current = list->head;

  while (index) {
    current = current->next;
    index--;
  }

  current->value = value;
  return list;
}