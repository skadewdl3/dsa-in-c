#include <stdio.h>
#include <stdlib.h>
#include "./../singly-linked-list/singly-linked-list.h"
#include "./queue-errors.h"

typedef struct QueueStruct {
  CharLL* items;
  CharNode* front;
  CharNode* rear;
} Queue;

Queue *Queue_create () {
  Queue *q = malloc(sizeof(Queue));
  q->items = CharLL_create();
  q->front = NULL;
  q->rear = NULL;
}

int Queue_is_empty (Queue *q) {
  return LL_is_empty(q->items);
}

void Queue_enqueue (Queue* q, char value) {
  if (Queue_is_empty(q)) {
    LL_push(q->items, value);
    q->front = q->items->head;
    q->rear = q->items->head;
  }
  else {
    q->rear = LL_push(q->items, value);
  }
}

void Queue_dequeue (Queue* q) {
  if (Queue_is_empty(q)) {
    return;
  }
  if (q->items->length == 1) {
    LL_shift(q->items);
    q->front = NULL;
    q->rear = NULL;
    return;
  }
  q->front = q->front->next;
  LL_shift(q->items);
}

void Queue_print (Queue *q) {
  LL_print(q->items);
}

void Queue_destroy (Queue *q) {
  LL_destroy(q->items);
  q->front = NULL;
  q->rear = NULL;
  free(q->front);
  free(q->rear);
  free(q);
}

