#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 100

typedef struct
{
  char data[100];
  int length;
} Stack;

Stack Stack_create()
{
  Stack st;
  for (int i = 0; i < MAX_LENGTH; i++)
  {
    st.data[i] = '0';
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

char Stack_get(Stack st, int i)
{
  if (Stack_is_empty(st))
    return -1;
  return st.data[i];
}

char Stack_peek(Stack st)
{
  if (Stack_is_empty(st))
    return -1;
  return st.data[st.length - 1];
}

void Stack_print(Stack st)
{
  printf("\nHEAD ->\t");
  for (int i = 0; i < st.length; i++)
  {
    printf("%c\t", Stack_get(st, i));
  }
  printf("\n ");
}

Stack Stack_push(Stack st, char element)
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

int main()
{
  char string[MAX_LENGTH];
  char reversed[MAX_LENGTH];
  scanf("%[^\n]", string);
  int length = strlen(string);

  Stack st = Stack_create();

  for (int i = 0; i < length; i++)
    st = Stack_push(st, string[i]);

  for (int i = 0; i < length; i++)
  {
    reversed[i] = Stack_peek(st);
    st = Stack_pop(st);
  }

  for (int i = 0; i < length; i++)
  {
    printf("%c", reversed[i]);
  }
}
