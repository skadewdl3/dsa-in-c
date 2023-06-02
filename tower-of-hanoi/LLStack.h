#include <stdio.h>
#include <stdlib.h>

#define ERROR_TEXT_COLOR "\x1b[31m"
#define ERROR_WARNING_COLOR "\x1b[33m"
#define ERROR_INFO_COLOR "\x1b[34m"
#define ERROR_RESET_COLOR "\x1b[m"

typedef enum {
  MEM_ALLOC_ERROR, OUT_OF_BOUNDS, LIST_EMPTY, LIST_DESTROYED, PRINT_EMPTY_LIST
} LL_errors;

void LL_print_error (char* type, char* message, char* solution) {
  printf(ERROR_TEXT_COLOR "\n%s:\n" ERROR_RESET_COLOR "%s\n" ERROR_INFO_COLOR "%s\n" ERROR_RESET_COLOR, type, message, solution);
}


void LL_print_warning (char* type, char* message, char* solution) {
  printf(ERROR_WARNING_COLOR "\n%s:\n" ERROR_RESET_COLOR "%s\n" ERROR_INFO_COLOR "%s\n" ERROR_RESET_COLOR, type, message, solution);
}


void LL_print_info (char* type, char* message, char* solution) {
  printf(ERROR_INFO_COLOR "\n%s:\n" ERROR_RESET_COLOR "%s\n" ERROR_INFO_COLOR "%s\n" ERROR_RESET_COLOR, type, message, solution);
}

void LL_error (LL_errors error_code) {
  switch (error_code) {
    case MEM_ALLOC_ERROR:
      LL_print_error("Runtime Error", "Memory allocation using malloc failed.", "Try freeing up some memory.");
      break;
    case OUT_OF_BOUNDS:
      LL_print_warning("Logical Error", "Index out of bounds. You tried accessing an element past the end of the list or before the beginning of the list.", "Try checking the index that you are accessing.");
      break;
    case LIST_EMPTY:
      LL_print_warning("Logical Error", "The list is empty. You cannot get/set an element in an empty list.", "Try adding an element to the list (push, insert, etc.) before trying to get/set an element.");
      break;
    case LIST_DESTROYED:
      LL_print_error("Logical Error", "You tried access the list after it has been destroyed.", "Try creating a new list or check for unintended LL_destroy calls.");
      break;
    
    case PRINT_EMPTY_LIST:
      LL_print_info("You tried to print an empty list", "This message was printed to avoid unintended operations.", "Try adding an element to the list using push/unshift/insert or check for unintended calls to pop/shift/delete.");
      break;
    
}
}

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

IntNode *IntLL_push(IntLL *list, int value)
{
  if (list->head == NULL) {
    LL_error(LIST_DESTROYED);
    exit(1);
  }
  IntNode *new_node = IntNode_create(value);
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

IntNode *IntLL_unshift(IntLL *list, int value)
{
  if (list->head == NULL) {
    LL_error(LIST_DESTROYED);
    exit(1);
  }
  IntNode *new_node = IntNode_create(value);
  if (list->length != 0) {
    new_node->next = list->head;
  }
  list->head = new_node;
  list->length++;
  return new_node;
}

int IntLL_pop(IntLL *list)
{
  if (list->head == NULL) {
    LL_error(LIST_DESTROYED);
    exit(1);
  }
  if (IntLL_is_empty(list)) {
    LL_error(LIST_EMPTY);
    return -1;
  }
  IntNode *current = list->head;
  int length = list->length;
  while (length - 2)
  {
    current = current->next;
    length--;
  }
  int value = current->next->value;
  IntNode_destroy(current->next);
  current->next = NULL;
  list->length--;
  return value;
}

int IntLL_shift(IntLL *list)
{
  if (list->head == NULL) {
    LL_error(LIST_DESTROYED);
    exit(1);
  }
  if (IntLL_is_empty(list)) {
    LL_error(LIST_EMPTY);
    return -1;
  }
  if (list->length == 1) {
    list->length = 0;
    return list->head->value;
  }
  IntNode *new_node_head = list->head->next;
  int value = list->head->value;
  IntNode_destroy(list->head);
  list->head = new_node_head;
  list->length--;
  return value;
}

void IntLL_print(IntLL *list)
{
  if (list->head == NULL) {
    LL_error(LIST_DESTROYED);
    exit(1);
  }
  if (list->length == 0) return;
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

IntLL *IntLL_insert(IntLL *list, int value, int index)
{
  if (list->head == NULL) {
    LL_error(LIST_DESTROYED);
    exit(1);
  }
  IntNode *new_node = IntNode_create(value);
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

int IntLL_get (IntLL *list, int index) {
  if (list->head == NULL) {
    LL_error(LIST_DESTROYED);
    exit(1);
  }
  if (IntLL_is_empty(list)) {
    LL_error(LIST_EMPTY);
    return -1;
  }
  if (index < 0 || index > list->length - 1) {
    LL_error(OUT_OF_BOUNDS);
    return -1;
  }

  IntNode* current = list->head;

  while (index) {
    current = current->next;
    index--;
  }

  return current->value;
}

IntLL *IntLL_set(IntLL *list, int value, int index) {
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

  current->value = value;
  return list;
}


typedef struct StackStruct {
  IntLL *items;
  IntNode* top;
  char name;
} Stack;

int Stack_size (Stack *st) {
  return st->items->length;
}

int Stack_get(Stack *st, int index) {
  return IntLL_get(st->items, index);
}

Stack *Stack_create (char name) {
  Stack *st = malloc(sizeof(Stack));
  st->items = IntLL_create(); 
  st->top = st->items->head;
  st->name = name;
  return st;
}

int Stack_is_empty (Stack* st) {
  return IntLL_is_empty(st->items);
}

void Stack_push (Stack* st, int value) {
  IntLL_unshift(st->items, value);
  st->top = st->items->head;
}

int Stack_pop (Stack *st) {
  int value = IntLL_shift(st->items);
  st->top = st->items->head;
  return value;
}

int Stack_peek (Stack *st) {
  return st->top->value; 
}

void Stack_print (Stack *st) {
  return IntLL_print(st->items);
}
