#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH 10

typedef struct DQ {
  int items[MAX_LENGTH];
  int* front;
  int* rear;
} DEQueue;

DEQueue *DEQueue_create() {
  DEQueue *q = malloc(sizeof(DEQueue));
  for (int i = 0; i < MAX_LENGTH; i++) {
    q->items[i] = NULL;
  }
  q->front = NULL;
  q->rear = NULL;
  return q;
}

int DEQueue_is_empty (DEQueue *q) {
  return q->front == NULL && q->rear == NULL;
}

int DEQueue_is_full (DEQueue *q) {
  return q-> rear == MAX_LENGTH - 1 && q->front == q->rear;
}

void DEQueue_destroy (DEQueue* q) {
  free(q);
}