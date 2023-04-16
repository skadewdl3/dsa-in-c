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
  int num_count = 0;
  int max = 0;
  int min = 0;
  scanf("%d", &num_count);

  Stack st = Stack_create();
  Stack removed = Stack_create();

  for (int i = 0; i < num_count; i++)
  {
    int temp;
    scanf("%d", &temp);

    if (Stack_is_empty(st))
    {
      st = Stack_push(st, temp);
    }
    else
    {

      while (Stack_peek(st) > temp)
      {
        int prev = Stack_peek(st);
        st = Stack_pop(st);
        removed = Stack_push(removed, prev);
      }
      st = Stack_push(st, temp);
      while (removed.length > 0)
      {
        st = Stack_push(st, Stack_peek(removed));
        removed = Stack_pop(removed);
      }
    }
  }
  max = Stack_peek(st);
  while (st.length > 0)
  {
    min = Stack_peek(st);
    st = Stack_pop(st);
  }

  printf("%d %d", max, min);
}