#include <stdio.h>
#include <string.h>
#include <math.h>
#define MAX_LENGTH 100

typedef struct
{
  int data[MAX_LENGTH];
  int length;
} Stack;

Stack Stack_create()
{
  Stack st;
  for (int i = 0; i < MAX_LENGTH; i++)
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

int eval(int a, char operator, int b)
{
  switch (operator)
  {
  case '+':
    return a + b;
    break;
  case '-':
    return a - b;
    break;
  case '*':
    return a * b;
    break;
  case '/':
    return a / b;
    break;
  case '^':
    return pow(a, b);
    break;
  case '%':
    return a % b;
    break;
  }
}
char Stack_get(Stack st, int i)
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
  // Infix statement entered by user
  char statement[MAX_LENGTH];
  printf("Enter postfix statement: ");
  scanf("%[^\n]", statement);
  int length = strlen(statement);

  // Create an empty stack
  Stack st = Stack_create();

  for (int i = 0; i < length; i++)
  {
    char cur = statement[i];
    if (cur == '+' || cur == '-' || cur == '*' || cur == '/' || cur == '^' || cur == '%')
    {
      int a = Stack_peek(st);
      st = Stack_pop(st);
      int b = Stack_peek(st);
      st = Stack_pop(st);
      int result = eval(a, cur, b);
      st = Stack_push(st, result);
    }
    else
    {
      st = Stack_push(st, cur - '0');
    }
    Stack_print(st);
  }

  printf("%d", Stack_peek(st));

  return 0;
}