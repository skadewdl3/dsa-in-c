#include <stdio.h>
#define MAX_LENGTH 20

typedef struct
{
  int data[20];
  int length;
} Stack;

Stack Stack_create()
{
  Stack st;
  for (int i = 0; i < 20; i++)
  {
    st.data[i] = 0;
  }
  st.length = 0;
  return st;
}

int Stack_is_empty(Stack st)
{
  return st.length == 0;
}

int Stack_is_full(Stack st)
{
  return st.length == MAX_LENGTH;
}

Stack Stack_push(Stack st, int element)
{
  if (Stack_is_full(st))
    return st;
  st.data[st.length] = element;
  st.length++;
  return st;
}

Stack Stack_pop(Stack st)
{
  if (Stack_is_empty(st))
    return st;
  st.length--;
  return st;
}

int Stack_peek(Stack st)
{
  if (Stack_is_empty(st))
    return -1;
  return st.data[st.length - 1];
}

int Stack_get(Stack st, int i)
{
  if (Stack_is_empty(st))
    return -1;
  return st.data[i];
}

void Stack_print(Stack st)
{
  printf("\nHEAD ->\t");
  for (int i = 0; i < st.length; i++)
  {
    printf("%d\t", Stack_get(st, i));
  }
  printf("\n ");
}

int main()
{
  int num_count = 10;

  Stack st = Stack_create();
  Stack removed = Stack_create();

  for (int i = 0; i < num_count; i++)
  {
    int temp;
    scanf("%d", &temp);
    st = Stack_push(st, temp);
  }

  for (int i = 0; i < st.length; i++)
  {
    if (Stack_get(st, i) < 0)
      printf("%d ", Stack_get(st, i));
  }

  return 0;
}