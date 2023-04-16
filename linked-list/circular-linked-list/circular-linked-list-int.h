#include <stdio.h>
#include <stdlib.h>

typedef struct IntLLNode
{
  int value;
  struct IntLLNode *next;
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
