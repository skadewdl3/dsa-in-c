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

int main()
{

  char statement[MAX_LENGTH];
  printf("Enter infix statement: ");
  scanf("%[^\n]", statement);
  int length = strlen(statement);

  // prefix statement to be calculated using stack
  char prefix[MAX_LENGTH];
  int prefix_length = 0;

  // Create an empty stack
  Stack st = Stack_create();

  st = Stack_push(st, '(');
  char c = ')';
  strncat(prefix, &c, 1);

  for (int i = 0; i < length; i++)
  {
    char cur = statement[length - 1 - i];
    // K+L-M*N+(O^P)*W/U/V*T+Q
    if (cur == '-' || cur == '+' || cur == '*' || cur == '/' || cur == '^' || cur == '%')
    {
      while (get_precedence(Stack_peek(st)) >= get_precedence(cur))
      {
        char temp = Stack_peek(st);
        strncat(prefix, &temp, 1);
        st = Stack_pop(st);
      }
      st = Stack_push(st, cur);
    }
    else if (cur == '(')
    {
      while (Stack_peek(st) != ')')
      {
        char temp = Stack_peek(st);
        strncat(prefix, &temp, 1);
        st = Stack_pop(st);
      }
    }
    else
    {
      strncat(prefix, &cur, 1);
    }
  }

  return 0;
}