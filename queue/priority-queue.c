#include <stdio.h>
#define MAX_LENGTH 10

typedef struct
{
  int value;
  int priority;
} PriorityQueueItem;

typedef struct
{
  PriorityQueueItem items[MAX_LENGTH];
  int front;
  int rear;
  int length;
} PriorityQueue;

int PriorityQueue_is_empty(PriorityQueue q)
{
  return q.rear == -1 && q.front == -1;
}

int PriorityQueue_is_full(PriorityQueue q)
{
  return q.rear - q.front == 1;
}

PriorityQueue PriorityQueue_create()
{
  PriorityQueue q;
  q.front = -1;
  q.rear = -1;
  q.length = 0;
  for (int i = 0; i < MAX_LENGTH; i++)
  {
    PriorityQueueItem q_item;
    q_item.value = 0;
    q_item.priority = 0;
    q.items[i] = q_item;
  }
  return q;
}

PriorityQueue PriorityQueue_enqueue(PriorityQueue q, PriorityQueueItem q_item)
{
  if (PriorityQueue_is_full(q))
    return q;
  if (PriorityQueue_is_empty(q))
  {
    q.rear == 0;
  }
  else
  {
    q.rear++;
  }
  printf("%d", q_item.priority);
  q.items[q.rear] = q_item;
  return q;
}

PriorityQueue PriorityQueue_dequeue(PriorityQueue q)
{
  if (PriorityQueue_is_empty(q))
    return q;
  if (q.rear == 0 && q.front == -1)
  {
    q.rear = -1;
    q.front = -1;
    return q;
  }
  else
  {
    q.front++;
  }
  return q;
}

int PriorityQueue_display(PriorityQueue q)
{
  printf("\n");
  for (int i = 0; i < MAX_LENGTH; i++)
  {
    printf("(%d): %d", q.items[i].priority, q.items[i].value);
    if (q.front == i)
      printf("\t->front");
    if (q.rear == i)
      printf("\t->rear");
    printf("\n");
  }
  printf("\n");
}

PriorityQueueItem create_queue_item(int priority, int value)
{
  PriorityQueueItem q_item;
  q_item.value = value;
  q_item.priority = priority;
  return q_item;
}

int main()
{
  PriorityQueue q = PriorityQueue_create();

  q = PriorityQueue_enqueue(q, create_queue_item(0, 1));
  q = PriorityQueue_enqueue(q, create_queue_item(2, 1));

  PriorityQueue_display(q);

  return 0;
}