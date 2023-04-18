#include <stdio.h>
#include <stdlib.h>

typedef struct CharLLNode
{
  char value;
  struct CharLLNode *next;
  struct CharLLNode *prev;
} CharNode;

typedef struct
{
  int length;
  CharNode *head;
} CharLL;

CharNode *CharNode_create(char val)
{
  CharNode *v = (CharNode*)malloc(sizeof(CharNode));
  if (v == NULL) {
    LL_error(MEM_ALLOC_ERROR);
    exit(1);
  }
  v->next = NULL;
  v->prev = NULL;
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

void CharLL_push (CharLL *list, char value) {
  if (list->head == NULL) {
    LL_error(LIST_DESTROYED);
    return;
  }
  CharNode *node = CharNode_create(value);
  if (list->length == 0) {
    list->head = node;
    node->next = node;
    node->prev = node;
  }
  else {
    CharNode *current = list->head;
    for (int i = 0; i < list->length - 1; i++) {
      current = current->next;
    }

    node->next = list->head;
    list->head->prev = node;

    node->prev = current;
    current->next = node;
  }
  list->length++;
}


void CharLL_pop (CharLL *list) {
  if (list->head == NULL) {
    LL_error(LIST_DESTROYED);
    return;
  }
  if (list->length == 0) {
    LL_error(LIST_EMPTY);
    return;
  }
  if (list->length == 1) {
    CharNode_destroy(list->head);
    list->head = CharNode_create(0);
    list->length = 0;
    return;
  }
  CharNode *current = list->head;
  for (int i = 0; i < list->length - 1; i++) {
    current = current->next;
  }
  
  CharNode *prev = current->prev;
  prev->next = list->head;
  list->head->prev = prev;
  CharNode_destroy(current);
  list->length--;
}

void CharLL_insert (CharLL *list, int value, int index) {
  if (list->head == NULL) {
    LL_error(LIST_DESTROYED);
    return;
  }
  if (index < 0 || index > list->length) {
    LL_error(OUT_OF_BOUNDS);
    return;
  }

  CharNode *new_node = CharNode_create(value);

  if (index == 0) {
    CharNode *next = list->head->next;
    CharNode *prev = list->head->prev;
    new_node->prev = prev;
    new_node->next = list->head;
    list->head = new_node;
  }
  else {
    CharNode *current = list->head;
    for (int i = 0; i < index; i++) {
      current = current->next;
    }
    CharNode *prev = current->prev;
    new_node->prev = prev;
    new_node->next = current;
    prev->next = new_node;
    current->prev = new_node;
  }
  list->length++;
}

void CharLL_delete (CharLL *list, int index) {
  if (list->head == NULL) {
    LL_error(LIST_DESTROYED);
    return;
  }
  if (index < 0 || index >= list->length) {
    LL_error(OUT_OF_BOUNDS);
    return;
  }
  if (list->length == 0) {
    LL_error(LIST_EMPTY);
    return;
  }
  if (list->length == 1) {
    CharNode_destroy(list->head);
    list->head = CharNode_create(0);
    list->length = 0;
    return;
  }
  if (index == 0) {
    CharNode *current = list->head;
    CharNode *next = current->next;
    CharNode *prev = current->prev;
    list->head = next;
    CharNode_destroy(current);
  }
  else {
    CharNode *current = list->head;
    for (int i = 0; i < index; i++) {
      current = current->next;
    }
    CharNode *prev = current->prev;
    CharNode *next = current->next;
    prev->next = next;
    next->prev = prev;
    CharNode_destroy(current);
  }
  list->length--;
}


void CharLL_print (CharLL *list) {
  if (list->head == NULL) {
    LL_error(LIST_DESTROYED);
    return;
  }
  if (list->length == 0) {
    printf("\nThe list is empty.");
  }
  CharNode *current = list->head;
  for (int i = 0; i < list->length; i++) {
    printf("%c ", current->value);
    current = current->next;
  }
}