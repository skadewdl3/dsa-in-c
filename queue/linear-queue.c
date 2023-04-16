#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH 2

typedef struct
{
  int items[MAX_LENGTH];
  int front;
  int rear;
} LinearQueue;

LinearQueue LinearQueue_create()
{
  LinearQueue q;
  for (int i = 0; i < MAX_LENGTH; i++)
  {
    q.items[i] = 0;
  }
  q.front = 0;
  q.rear = 0;
  return q;
}

LinearQueue LinearQueue_is_empty (LinearQueue q) {
  return q.front == 0 && q.rear == 0;
}


LinearQueue LinearQueue_is_full (LinearQueue q) {
  return q.front == MAX_LENGTH;
}

LinearQueue LinearQueue_enqueue(LinearQueue q, int val)
{
  if (q.rear == MAX_LENGTH)
    return q;
  q.items[q.rear] = val;
  q.rear++;
  return q;
}

LinearQueue LinearQueue_dequeue(LinearQueue q)
{
  if (q.front >= q.rear)
    return q;
  q.front++;
  return q;
}

void LinearQueue_display(LinearQueue q)
{
  printf("\nLinearQueue:\n");
  for (int i = q.front; i < q.rear; i++)
  {
    printf("%d\t", q.items[i]);
  }
  printf("\n");
}

int main()
{

  LinearQueue q = LinearQueue_create();

  q = LinearQueue_enqueue(q, 1);
  q = LinearQueue_enqueue(q, 2);
  LinearQueue_display(q);
  q = LinearQueue_dequeue(q);
  LinearQueue_display(q);
  q = LinearQueue_dequeue(q);
  LinearQueue_display(q);
  q = LinearQueue_dequeue(q);
  LinearQueue_display(q);

  return 0;
}