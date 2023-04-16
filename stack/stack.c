#include <stdio.h>
#define MAX_LENGTH 20;

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

int main()
{
  Stack st = Stack_create();
  int operation;
  int el;
  while (1)
  {
    scanf("%d", &operation);
    switch (operation)
    {
    case 1:
      scanf("%d ", &el);
      st = Stack_push(st, el);
      break;
    case 2:
      printf("%d ", Stack_peek(st));
      st = Stack_pop(st);
      break;
    case 3:
      printf("%d ", Stack_peek(st));
      break;
    case 4:
      printf("%s ", Stack_is_empty(st) ? "true" : "false");
      break;
    case 5:
      printf("%s ", Stack_is_empty(st) ? "true" : "false");
      break;
    case 6:
      return 0;
    }
  }
}