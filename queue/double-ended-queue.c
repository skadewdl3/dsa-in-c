#include <stdio.h>
#include <math.h>
#define MAX_LENGTH 5

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

int DEQueue_get (DEQueue q, int index) {
  if (DEQueue_is_empty(q))
    return -1;
  if (index < 0 || index >= MAX_LENGTH) {
    return -1;
  }
  return q.items[q.front + index];
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

int DEQueue_get_front (DEQueue q) {
  return q.items[q.front];
}

int DEQueue_get_rear (DEQueue q) {
  return q.items[q.rear];
}

int DEQueue_display_minimal (DEQueue q) {
  int index = q.front;
  if (q.rear == -1) {
    while (index != MAX_LENGTH - 1) {
      // printf("%d %d\n\n", q.front, q.rear);
      printf("%d ", q.items[index]);
      index = get_index(index + 1);
    }
  } else {
    while (index != q.rear) {
      // printf("%d %d\n\n", q.front, q.rear);
      printf("%d ", q.items[index]);
      index = get_index(index + 1);
    }
  }
  printf("%d ", q.items[index]);
}

int main()
{

  int operation;
  int temp;
  DEQueue q = DEQueue_create();
  while (1) {

    scanf("%d%*c", &operation);

    switch (operation) {
      case 1:
        if (DEQueue_is_full(q)) {
          printf("full ");
        }
        else {
          scanf("%d%*c", &temp);
          q = DEQueue_add_front(q, temp);
        }
        break;
      case 2:
      if (DEQueue_is_full(q)) {
          printf("full ");
        }
        else {

        scanf("%d%*c", &temp);
        q = DEQueue_add_rear(q, temp);
        }
        break;
      case 3:
        if (DEQueue_is_empty(q)) {
          printf("empty ");
        }
        else {
          printf("%d ", DEQueue_get_front(q));
        q = DEQueue_remove_front(q);
        }
        break;
      case 4:
        if (DEQueue_is_empty(q)) {
          printf("empty ");
        }
        else {
          printf("%d ", DEQueue_get_rear(q));
          q = DEQueue_remove_rear(q);
        }
        break;
      case 5:
        if (DEQueue_is_empty(q)) {
          printf("empty ");
        }
        else {
          DEQueue_display_minimal(q);
        }
        break;
      default:
        return 0;
    }

  }

}