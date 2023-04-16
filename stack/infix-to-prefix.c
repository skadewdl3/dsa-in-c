#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX 100

char stack[MAX];
char statement[MAX];
char prefix[MAX];
int top = -1;

void push(char c)
{
  if (top >= MAX - 1)
  {
    printf("Stack overflow\n");
    exit(1);
  }
  stack[++top] = c;
}

char pop()
{
  if (top < 0)
  {
    printf("Stack underflow\n");
    exit(1);
  }
  return stack[top--];
}

bool is_empty()
{
  return top == -1;
}

int precedence(char symbol)
{
  switch (symbol)
  {
  case '^':
    return 3;
  case '/':
  case '*':
  case '%':
    return 2;
  case '+':
  case '-':
    return 1;
  default:
    return 0;
  }
}

void infix_to_prefix()
{
  int prefix_length = 0;
  char symbol, next;
  for (int i = 0; i < strlen(statement); i++)
  {
    symbol = statement[i];
    switch (symbol)
    {
    case '(':
      push(symbol);
      break;
    case ')':
      while ((next = pop()) != '(')
        prefix[prefix_length++] = next;
      break;
    case '+':
    case '-':
    case '*':
    case '/':
    case '^':
    case '%':
      while (!is_empty() && precedence(stack[top]) > precedence(symbol))
        prefix[prefix_length++] = pop();
      push(symbol);
      break;
    default:
      prefix[prefix_length++] = symbol;
    }
  }
  while (!is_empty())
  {
    prefix[prefix_length++] = pop();
  }
  prefix[prefix_length] = '\0';
}

int main()
{
  gets(statement);
  strrev(statement);
  for (int i = 0; i < strlen(statement); i++)
  {
    if (statement[i] == ')')
      statement[i] = '(';
    else if (statement[i] == '(')
      statement[i] = ')';
  }
  infix_to_prefix();
  strrev(prefix);
  printf("%s", prefix);
}