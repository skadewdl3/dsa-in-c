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

int get_precedence(char c)
{
  switch (c)
  {
  case '+':
  case '-':
    return 0;
    break;
  case '*':
  case '/':
  case '%':
    return 1;
    break;
  case '^':
    return 2;
    break;
  default:
    return -1;
    break;
  }
}

int is_delimiter(char delimiter)
{
  // Only considering [], (), {} as delimiters
  switch (delimiter)
  {
  case '[':
    return 1;
  case '(':
    return 2;
  case '{':
    return 3;
    break;
  case ']':
    return -1;
    break;
  case ')':
    return -2;
    break;
  case '}':
    return -3;
    break;
  default:
    return 0;
    break;
  }
}

int main()
{
  Stack st = Stack_create();

  char statement[MAX_LENGTH];
  printf("Enter statement: ");
  scanf("%[^\n]", statement);
  int length = strlen(statement);

  int error_index = -1;

  for (int i = 0; i < length; i++)
  {
    char cur = statement[i];

    if (is_delimiter(cur) > 0)
    {
      st = Stack_push(st, cur);
    }

    if (is_delimiter(cur) < 0)
    {
      if (is_delimiter(cur) == -1 * is_delimiter(Stack_peek(st)))
      {
        st = Stack_pop(st);
      }
      else
      {
        error_index = i;
        break;
      }
    }
  }

  if (error_index >= 0 || !Stack_is_empty(st))
  {
    printf("Delimiter mismatch");
  }
  else
  {
    printf("All delimiters match");
  }
}
