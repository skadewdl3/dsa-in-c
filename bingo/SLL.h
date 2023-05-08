#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
  int info;
  struct node *next;
} SLLNode;

typedef struct {
  SLLNode *head;
  int length;
} SLL;

SLLNode *createNode(int info)
{
  SLLNode *temp;
  temp = (SLLNode *)malloc(sizeof(SLLNode));
  temp->info = info;
  temp->next = NULL;
  return temp;
}

SLL *createList()
{
  SLL *list;
  list = (SLL *)malloc(sizeof(SLL));
  list->head = NULL;
  list->length = 0;
  return list;
}

void insertAtFront(SLL *list, int info)
{
  SLLNode * temp = createNode(info);
  temp->next = list->head;
  list->head = temp;
  list->length++;
}

void insertAtEnd(SLL *list, int info)
{
  SLLNode *temp = createNode(info);
  if(list->head == NULL) {
    list->head = temp;
  } else {
    SLLNode *temp1 = list->head;
    while(temp1->next != NULL) {
      temp1 = temp1->next;
    }
    temp1->next = temp;
  }
  list->length++;
}

void insertAtPosition(SLL *list, int info, int pos)
{
  SLLNode *temp = createNode(info);
  if(pos == 0) {
    temp->next = list->head;
    list->head = temp;
  } else {
    SLLNode *temp1 = list->head;
    for(int i = 0; i < pos - 1; i++) {
      temp1 = temp1->next;
    }
    temp->next = temp1->next;
    temp1->next = temp;
  }
  list->length++;
}

void deleteAtFront(SLL *list)
{
  if(list->head == NULL) {
    printf("List is empty\n");
  } else {
    SLLNode *temp = list->head;
    list->head = list->head->next;
    free(temp);
    list->length--;
  }
}

void deleteAtEnd(SLL *list)
{
  if(list->head == NULL) {
    printf("List is empty\n");
  } else {
    SLLNode *temp = list->head;
    while(temp->next->next != NULL) {
      temp = temp->next;
    }
    free(temp->next);
    temp->next = NULL;
    list->length--;
  }
}

void deleteAtPosition(SLL *list, int pos)
{
  if(list->head == NULL) {
    printf("List is empty\n");
  } else {
    SLLNode *temp = list->head;
    if(pos == 0) {
      list->head = list->head->next;
      free(temp);
    } else {
      for(int i = 0; i < pos - 1; i++) {
        temp = temp->next;
      }
      SLLNode *temp1 = temp->next;
      temp->next = temp1->next;
      free(temp1);
    }
    list->length--;
  }
}

void replace (SLL *list, int info, int pos)
{
  if(list->head == NULL) {
    printf("List is empty\n");
  } else {
    SLLNode *temp = list->head;
    for(int i = 0; i < pos; i++) {
      temp = temp->next;
    }
    temp->info = info;
  }
}

int get (SLL *list, int pos) {
  if(list->head == NULL) {
    printf("List is empty\n");
  } else {
    SLLNode *temp = list->head;
    for(int i = 0; i < pos; i++) {
      temp = temp->next;
    }
    return temp->info;
  }
}


void print_list(SLL *list) {
  SLLNode *temp = list->head;
  while(temp != NULL) {
    if (temp->info == 88) {
      printf("  X ");
    }
    else if (temp->info == 95) {
      printf("  _ ");
    }
    else {
      printf("%3d ", temp->info);
    }
    temp = temp->next;
  }
  printf("\n");
}