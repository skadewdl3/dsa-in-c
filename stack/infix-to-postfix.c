#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX 100

char stack[MAX];
char statement[MAX];
char postfix[MAX];
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

void infix_to_postfix()
{
  int postfix_length = 0;
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
        postfix[postfix_length++] = next;
      break;
    case '+':
    case '-':
    case '*':
    case '/':
    case '^':
    case '%':
      while (!is_empty() && precedence(stack[top]) >= precedence(symbol))
        postfix[postfix_length++] = pop();
      push(symbol);
      break;
    default:
      postfix[postfix_length++] = symbol;
    }
  }
  while (!is_empty())
  {
    postfix[postfix_length++] = pop();
  }
  postfix[postfix_length] = '\0';
}

int main()
{
  gets(statement);
  infix_to_postfix();
  printf("%s", postfix);
}