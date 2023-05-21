#include <stdio.h>
#include <string.h>
#include "./../stack.h"

int precedence (char operator) {
  switch (operator) {
    case '+':
    case '-':
      return 1;
    case '*':
    case '/':
    case '%':
      return 2;
    case '^':
      return 3;
    default:
      return -1;
  }
}

int is_operator (char operator) {
  return operator == '+' || operator == '-' || operator == '*' || operator == '/' || operator == '%' || operator == '^';
}
 

int main () {
  char infix[] = "a^b*c";
  int length = strlen(infix);
  char reversed_infix[length];

  for (int i = 0; i < length; i++) {
    reversed_infix[i] = infix[length - 1 - i];
    if (reversed_infix[i] == '(') {
      reversed_infix[i] = ')';
    }
    else if (reversed_infix[i] == ')') {
      reversed_infix[i] = '(';
    }
  }

  char postfix[length];
  int postfix_length = 0;
  
  CharStack *stack = CharStack_create();

  for (int i = 0; i < length; i++) {

    char current = reversed_infix[i];

    if (is_operator(current)) {
      while (precedence(current) < precedence(Stack_peek(stack))) {
        postfix[postfix_length++] = Stack_pop(stack);
      }
      Stack_push(stack, current);
    }

    else if (current == '(') {
      Stack_push(stack, current);
    }

    else if (current == ')') {
      while (Stack_peek(stack) != '(') {
        postfix[postfix_length++] = Stack_pop(stack);
      }
      Stack_pop(stack);
    }

    else if (current != ' ') {
      postfix[postfix_length++] = current;
    }
  }

  while (!Stack_is_empty(stack)) {
    if (Stack_peek(stack) == '(') Stack_pop(stack);
    else postfix[postfix_length++] = Stack_pop(stack);
  }

  for (int i = 0; i < postfix_length; i++) printf("%c", postfix[postfix_length - 1 - i]);

}