#include <stdio.h>
#include <stdlib.h>
#include "./binary-tree.h"

typedef struct {
  Node** data;
  int size;
  int max_size;
} Stack;

Stack* Stack_create () {
  Stack* stack = (Stack*)malloc(sizeof(Stack));
  stack->data = malloc(sizeof(int) * 1);
  stack->size = 0;
  stack->max_size = -1;
  return stack;
}

void Stack_destroy (Stack* stack) {
  free(stack->data);
  free(stack);
}

void Stack_set_max_size (Stack* stack, int size) {
  stack->max_size = size;
  // do clipping off operation
}

int Stack_is_empty (Stack* stack) {
  return stack->size == 0;
}

int Stack_is_full (Stack* stack) {
  return stack->size == stack->max_size;
}

void Stack_push (Stack* stack, Node* node) {
  if (Stack_is_full(stack)) {
    // print error
    return;
  }
  stack->data = realloc(stack->data, sizeof(Node*) * (stack->size + 1));
  stack->data[stack->size] = node;
  stack->size++;
}

Node* Stack_pop (Stack* stack) {
  if (Stack_is_empty(stack)) {
    // print error
    return NULL;
  }
  Node* deleted = stack->data[stack->size - 1];
  stack->data = realloc(stack->data, sizeof(Node*) * (stack->size - 1));
  stack->size--;
  return deleted;
}

Node* Stack_peek (Stack* stack) {
  if (Stack_is_empty(stack)) {
    // print error
    return NULL;
  }
  return stack->data[stack->size - 1];
}

void Stack_print (Stack* stack) {
  for (int i = 0; i < stack->size; i++) {
    printf("%s%d%s ", i == 0 ? "[" : "" ,stack->data[i]->value, i == 0 ? "]" : "");
  }
  printf("\n");
}

void traverse_preorder (Tree* tree) {
  Stack* stack = Stack_create();

  Stack_push(stack, tree->root);

  while (!Stack_is_empty(stack)) {
    Node* node = Stack_pop(stack);
    
    if (node->right != NULL) {
      Stack_push(stack, node->right);
    }
    if (node->left != NULL) {
      Stack_push(stack, node->left);
    }
    printf("%d ", node->value);
  }
}


void traverse_inorder (Tree* tree) {
  Stack* stack = Stack_create();

  Node* current = tree->root;
  Stack_push(stack, current);

  while (!Stack_is_empty(stack)) {
    if (current != NULL) {
      current = current->left; 
      Stack_push(stack, current);
    }
    if (current == NULL) {
      current = Stack_pop(stack);
      printf("%d", current->value);
      current = current->right;
      Stack_push(stack, current);
    }
  }
}

int main () {

  // preorder traversal


  Tree* tree = BT_create_with_root(1);
  Node* root = tree->root;

  root->left = create_node(2);
  root->left->left = create_node(4);
  root->left->right = create_node(5);
  root->left->left->left = create_node(7);
  root->left->left->left->right = create_node(9);


  root->right = create_node(3);
  root->right->right = create_node(6);
  root->right->right->right = create_node(8);

  traverse_inorder(tree);

  return 0;
}
