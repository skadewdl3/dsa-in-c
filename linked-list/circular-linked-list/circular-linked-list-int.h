#include <stdio.h>
#include <stdlib.h>

typedef struct IntLLNode
{
  int value;
  struct IntLLNode *next;
  struct IntLLNode *prev;
} IntNode;

typedef struct
{
  int length;
  IntNode *head;
} IntLL;

IntNode *IntNode_create(int val)
{
  IntNode *v = (IntNode *)malloc(sizeof(IntNode));
  if (v == NULL) {
    LL_error(MEM_ALLOC_ERROR);
    exit(1);
  }
  v->next = NULL;
  v->prev = NULL;
  v->value = val;
  return v;
}

void IntNode_destroy(IntNode *node)
{
  free(node);
}

IntLL *IntLL_create()
{
  IntLL *list = (IntLL*)malloc(sizeof(IntLL));
  IntNode *head = IntNode_create(0);
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

  for (int i = 0; i < list->length - 1; i++) {
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

void IntLL_push (IntLL *list, int value) {
  if (list->head == NULL) {
    LL_error(LIST_DESTROYED);
    return;
  }
  IntNode *node = IntNode_create(value);
  if (list->length == 0) {
    node->prev = node;
    node->next = node;
    list->head = node;
  }
  else {
    IntNode *current = list->head;
    for (int i = 0; i < list->length - 1; i++) {
      current = current->next;
    }
    // link node with head
    node->next = list->head;
    list->head->prev = node;

    // link node with current
    node->prev = current;
    current->next = node;
  }
  list->length++; 
}

void IntLL_pop (IntLL *list) {
  if (list->head == NULL) {
    LL_error(LIST_DESTROYED);
    return;
  }
  if (list->length == 0) {
    LL_error(LIST_EMPTY);
    return;
  }
  if (list->length == 1) {
    IntNode_destroy(list->head);
    list->head = IntNode_create(0);
    list->length = 0;
    return;
  }
  IntNode *current = list->head;
  for (int i = 0; i < list->length - 1; i++) {
    current = current->next;
  }
  
  IntNode *prev = current->prev;
  prev->next = list->head;
  list->head->prev = prev;
  IntNode_destroy(current);
  list->length--;
}

void IntLL_insert (IntLL *list, int value, int index) {
  if (list->head == NULL) {
    LL_error(LIST_DESTROYED);
    return;
  }
  if (index < 0 || index > list->length) {
    LL_error(OUT_OF_BOUNDS);
    return;
  }

  IntNode *new_node = IntNode_create(value);

  if (index == 0) {
    IntNode *next = list->head->next;
    IntNode *prev = list->head->prev;
    new_node->prev = prev;
    new_node->next = list->head;
    list->head = new_node;
  }
  else {
    IntNode *current = list->head;
    for (int i = 0; i < index; i++) {
      current = current->next;
    }
    IntNode *prev = current->prev;
    new_node->prev = prev;
    new_node->next = current;
    prev->next = new_node;
    current->prev = new_node;
  }
  list->length++;
} 

void IntLL_delete (IntLL *list, int index) {
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
    IntNode_destroy(list->head);
    list->head = IntNode_create(0);
    list->length = 0;
    return;
  }
  if (index == 0) {
    IntNode *current = list->head;
    IntNode *next = current->next;
    IntNode *prev = current->prev;
    list->head = next;
    IntNode_destroy(current);
  }
  else {
    IntNode *current = list->head;
    for (int i = 0; i < index; i++) {
      current = current->next;
    }
    IntNode *prev = current->prev;
    IntNode *next = current->next;
    prev->next = next;
    next->prev = prev;
    IntNode_destroy(current);
  }
  list->length--;
}

void IntLL_print (IntLL *list) {
  if (list->head == NULL) {
    LL_error(LIST_DESTROYED);
    return;
  }
  if (list->length == 0) {
    printf("\nThe list is empty.");
  }
  IntNode *current = list->head;
  for (int i = 0; i < list->length; i++) {
    printf("\n%d ", current->value);
    current = current->next;
  }
  printf("\n");
}