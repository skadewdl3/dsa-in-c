#include <stdio.h>
#include <math.h>
#define MAX_LENGTH 10

typedef struct
{
  int items[MAX_LENGTH];
  int front;
  int rear;
} DEQueue;

int get_index(int i)
{
  return i % MAX_LENGTH;
}

DEQueue DEQueue_create()
{
  DEQueue q;
  for (int i = 0; i < MAX_LENGTH; i++)
  {
    q.items[i] = 0;
  }
  q.front = -1;
  q.rear = -1;
  return q;
}

int DEQueue_is_full(DEQueue q)
{
  return (q.rear + 1) % MAX_LENGTH == q.front;
}

int DEQueue_is_empty(DEQueue q)
{
  // printf("%d %d", q.front, q.rear);
  return q.front == -1 && q.rear == -1;
}

DEQueue DEQueue_add_front(DEQueue q, int el)
{
  if (DEQueue_is_full(q))
  {
    return q;
  }
  if (q.front == -1 && q.rear == -1)
  {
    q.front = MAX_LENGTH - 1;
  }
  else
    q.front = get_index(q.front - 1);
  q.items[q.front] = el;
  return q;
}

DEQueue DEQueue_remove_front(DEQueue q)
{
  if (DEQueue_is_empty(q))
    return q;
  if (q.front == MAX_LENGTH - 1 && q.rear == -1)
  {
    q.items[q.front] = 0;
    q.front = -1;
    q.rear = -1;
    return q;
  }
  q.items[q.front] = 0;
  q.front = get_index(q.front + 1);
  return q;
}

DEQueue DEQueue_add_rear(DEQueue q, int el)
{
  if (DEQueue_is_full(q))
    return q;
  if (q.front == -1 && q.rear == -1)
  {
    q.front = 0;
    q.rear = 0;
  }
  else
  {

    q.rear = get_index(q.rear + 1);
  }
  q.items[q.rear] = el;
  return q;
}

DEQueue DEQueue_remove_rear(DEQueue q)
{
  if (DEQueue_is_empty(q))
    return q;
  if (q.front == 0 && q.rear == 0)
  {
    q.front = -1;
    q.rear = -1;
    q.items[0] = 0;
    return q;
  }
  q.items[q.rear] = 0;
  q.rear = get_index(q.rear - 1);
  return q;
}

void DEQueue_display(DEQueue q)
{
  if (DEQueue_is_empty(q))
  {

    printf("Queue is empty.\n\n");
    return;
  }
  for (int i = 0; i < MAX_LENGTH; i++)
  {
    if (q.rear == i && q.front == i)
    {
      printf("%d\t-> front & rear\n", q.items[0]);
    }
    else if (get_index(i) == q.front)
    {
      printf("%d\t-> front\n", q.items[i]);
    }
    else if (get_index(i) == q.rear)
    {

      printf("%d\t-> rear\n", q.items[i]);
    }
    else
    {
      printf("%d\n", q.items[i]);
    }
  }
  printf("\n");
}

int main()
{
  DEQueue q = DEQueue_create();
  DEQueue_display(q);
  q = DEQueue_add_front(q, 1);
  DEQueue_display(q);
  q = DEQueue_add_rear(q, 2);
  DEQueue_display(q);
  q = DEQueue_add_front(q, 2);
  DEQueue_display(q);
  q = DEQueue_remove_front(q);
  q = DEQueue_remove_front(q);
  DEQueue_display(q);
}