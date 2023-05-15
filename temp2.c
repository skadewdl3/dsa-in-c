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
    list->head->next = list->head;
  }
  else
  {
    IntNode *current = list->head;
    for (int i = 0; i < list->length - 1; i++)
    {
      current = current->next;
    }
    new_node->next = list->head;
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
  else {
    new_node->next = new_node;
  }
  list->head = new_node;
  list->length++;

  IntNode *current = list->head;
  for (int i = 0; i < list->length - 1; i++) {
    current = current->next;
  }
  current->next = list->head;
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
  current->next = list->head;
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
  IntNode *current = list->head;
  for (int i = 0; i < list->length - 1; i++) {
    current = current->next;
  }
  current->next = list->head;
  return value;
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
    for (int i = 0; i < list->length; i++)
    {
      printf("%d ", current->value);
      current = current->next;
    }
  }
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
    list->head->next = list->head;
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
      IntLL_unshift(list, value);
    }
  }
  list->length++;
  return list;
}

int IntLL_delete(IntLL *list, int index)
{
  int deleted = -1;
  if (list->head == NULL) {
    LL_error(LIST_DESTROYED);
    exit(1);
  }
  if (IntLL_is_empty(list))
  {
    LL_error(LIST_EMPTY);
    return deleted;
  }
  if (index < 0 || index > list->length - 1) {
    LL_error(OUT_OF_BOUNDS);
    return deleted;
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
      deleted = to_delete->value;
      current->next = to_delete->next;
      IntNode_destroy(to_delete);
    }
    else
    {
      deleted = list->head->value;
      list->head = current->next;
      IntNode_destroy(current);
    }
  }
  list->length--;
  return deleted;
}
int IntLL_search (IntLL* list, int value) {
  if (list->head == NULL) {
    LL_error(LIST_DESTROYED);
    exit(1);
  }
  if (IntLL_is_empty(list)) return -1;

  IntNode* current = list->head;
  for (int i = 0; i < list->length; i++) {
    if (current->value == value) return i;
    current = current->next;
  }
  return -1;
}

int main () {

    IntLL* list = IntLL_create();

    int choice;
    int operand1;
    int operand2;
    int index;

    while (1) {
        scanf("%d%*c", &choice);
        switch (choice) {
            case 1:
                scanf("%d%*c", &operand1);
                IntLL_unshift(list, operand1);
                break;
            case 2:
                scanf("%d%*c", &operand1);
                IntLL_push(list, operand1);
                break;
            case 3:
                scanf("%d", &operand1);
                int index = IntLL_search(list, operand1);
                scanf("%d", &operand2);
                IntLL_insert(list, operand2, index + 1);
                break;
            case 4:
                if (list->length == 0) {
                    printf("empty ");
                }
                printf("%d ", IntLL_shift(list));
                break;
                
            case 5:
                if (list->length == 0) {
                    printf("empty ");
                }
                printf("%d ", IntLL_pop(list));
                break;
                
            case 6:
                if (list->length == 0) {
                    printf("empty ");
                }
                scanf("%d", &operand1);
                index = IntLL_search(list, operand1);
                printf("%d ", IntLL_delete(list, index + 1));
                break;
            case 7:
                if (list->length == 0) {
                    printf("empty ");
                    break;
                }
                IntLL_print(list);
                break;
            case 8:
                scanf("%d%*c", &operand1);
                index = IntLL_search(list, operand1); 
                if (index == -1) printf("absent ");
                else printf("present at %d ", index + 1);
                break;
            case 9:
                return 0;

        }
    }    
}