#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_LENGTH 2

typedef struct
{
  int items[MAX_LENGTH];
  int front;
  int rear;
} CircularQueue;

CircularQueue CircularQueue_create()
{
  CircularQueue q;
  for (int i = 0; i < MAX_LENGTH; i++)
  {
    q.items[i] = 0;
  }
  q.front = 0;
  q.rear = 0;
  return q;
}

int CircularQueue_is_empty(CircularQueue q)
{
  return q.front == q.rear;
}

int CircularQueue_is_full(CircularQueue q)
{
  if (abs(q.front - q.rear) > MAX_LENGTH / 2)
  {
    return abs(q.front - (q.rear - MAX_LENGTH / 2)) == 1;
  }
  else
  {
    return q.front - q.rear == 1;
  }
}

CircularQueue CircularQueue_enqueue(CircularQueue q, int val)
{
  // printf("is full: %d", CircularQueue_is_full(q));
  if (CircularQueue_is_full(q))
    return q;
  if (q.rear == MAX_LENGTH - 1)
    q.rear = 0;
  q.items[q.rear] = val;
  if (q.rear == MAX_LENGTH)
    q.rear = 0;
  else
    q.rear++;
  // printf("rear is now: %d", q.rear);
  return q;
}

CircularQueue CircularQueue_dequeue(CircularQueue q)
{
  if (q.front >= q.rear)
    return q;
  q.front++;
  return q;
}

void CircularQueue_display(CircularQueue q)
{
  // printf("\nCircularQueue:\n");
  for (int i = q.front; i < q.rear; i++)
  {
    printf("%d\t", q.items[i]);
  }
  printf("\n");
}

int main()
{

  CircularQueue q = CircularQueue_create();

  q = CircularQueue_enqueue(q, 1);
  q = CircularQueue_enqueue(q, 2);

  CircularQueue_display(q);

  

  return 0;
}