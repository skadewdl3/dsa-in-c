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

IntLL IntLL_create()
{
  IntLL list;
  IntNode *head = IntNode_create(0);
  list.head = head;
  list.length = 0;
  return list;
}

void IntLL_destroy(IntLL list)
{
  IntNode *prev = NULL;
  IntNode *current = list.head;
  while (current->next != NULL)
  {
    prev = current;
    current = current->next;
    IntNode_destroy(prev);
  }
  IntNode_destroy(current);
}

int IntLL_is_empty(IntLL list)
{
  return list.length == 0;
}

IntLL IntLL_push(IntLL list, int value)
{
  IntNode *new_node = IntNode_create(value);
  if (IntLL_is_empty(list))
  {
    list.head = new_node;
  }
  else
  {
    IntNode *current = list.head;
    while (current->next != NULL)
    {
      current = current->next;
    }
    new_node->prev = current;
    current->next = new_node;
  }
  list.length++;
  return list;
}

IntLL IntLL_unshift(IntLL list, int value)
{
  IntNode *new_node = IntNode_create(value);
  list.head->prev = new_node;
  new_node->next = list.head;
  new_node->prev = NULL;
  list.head = new_node;
  list.length++;
  return list;
}

IntLL IntLL_pop(IntLL list)
{
  if (IntLL_is_empty(list))
  {
    LL_error(LIST_EMPTY);
    return list;
  }
  IntNode *current = list.head;
  int length = list.length;
  while (length - 2)
  {
    current = current->next;
    length--;
  }
  IntNode_destroy(current->next);
  current->next = NULL;
  list.length--;
  return list;
}

IntLL IntLL_shift(IntLL list)
{
  if (IntLL_is_empty(list))
  {
    LL_error(LIST_EMPTY);
    return list;
  }
  IntNode *new_node_head = list.head->next;
  IntNode_destroy(list.head);
  new_node_head->prev = NULL;
  list.head = new_node_head;
  return list;
}

void IntLL_print(IntLL list)
{
  IntNode *current = list.head;
  while (current != NULL)
  {
    printf("\n%d", current->value);
    current = current->next;
  }
  printf("\n");
}

IntLL IntLL_insert(IntLL list, int value, int index)
{
  if (index < 0 || index > list.length - 1)
  {
    LL_error(OUT_OF_BOUNDS);
    return list;
  }
  IntNode *new_node = IntNode_create(value);
  if (IntLL_is_empty(list))
  {
    list.head = new_node;
  }
  else
  {
    IntNode *current = list.head;
    int length = list.length;
    if (index > 0)
    {

      while (index - 1)
      {
        current = current->next;
        index--;
      }
      IntNode *old = current->next;
      old->prev = new_node;
      new_node->next = old;

      new_node->prev = current;
      current->next = new_node;
    }
    else
    {
      new_node->next = current;
      list.head = new_node;
    }
  }
  list.length++;
  return list;
}

IntLL IntLL_delete(IntLL list, int index)
{
  if (IntLL_is_empty(list))
  {
    LL_error(LIST_EMPTY);
    return list;
  }
  if (index < 0 || index > list.length - 1)
  {
    LL_error(OUT_OF_BOUNDS);
    return list;
  }
  else
  {
    IntNode *current = list.head;
    if (index > 0)
    {

      while (index - 1)
      {
        current = current->next;
        index--;
      }

      IntNode *to_delete = current->next;
      to_delete->next->prev = current;
      current->next = to_delete->next;
      IntNode_destroy(to_delete);
    }
    else
    {
      list.head = current->next;
      list.head->prev = NULL;
      IntNode_destroy(current);
    }
  }
  list.length--;
  return list;
}

IntLL IntLL_reverse(IntLL list)
{

  if (IntLL_is_empty(list))
  {
    LL_error(LIST_EMPTY);
    return list;
  }

  IntNode *current = list.head;
  IntNode *head_next = NULL;

  while (current->next != NULL)
  {
    IntNode *new_next = current->prev;
    IntNode *new_prev = current->next;
    current->next = new_next;
    current->prev = new_prev;
    head_next = current;
    current = new_prev;
  }
  current->next = head_next;
  current->prev = NULL;
  list.head = current;
  return list;
}

int IntLL_get (IntLL list, int index) {
  if (index < 0 || index > list.length - 1) {
    LL_error(OUT_OF_BOUNDS);
    return -1;
  }
  
  if (IntLL_is_empty(list)) {
    LL_error(LIST_EMPTY);
    return -1;
  }

  IntNode* current = list.head;

  while (index) {
    current = current->next;
    index--;
  }

  return current->value;
}

IntLL IntLL_set(IntLL list, int value, int index) {
  if (index < 0 || index > list.length - 1) {
    LL_error(OUT_OF_BOUNDS);
    return list;
  }
  
  if (IntLL_is_empty(list)) {
    LL_error(LIST_EMPTY);
    return list;
  }

  IntNode* current = list.head;

  while (index) {
    current = current->next;
    index--;
  }

  current->value = value;
  return list;
}