#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
  char value;
  struct TreeNode* left;
  struct TreeNode* right;
} Node;

typedef struct {
  int depth;
  Node* root;
} Tree;

Node* create_node (char value) {
  Node* node = (Node*)malloc(sizeof(Node));
  node->value = value;
  node->left = NULL;
  node->right = NULL;
  return node;
}

Tree* BT_create() {
  Tree* tree = (Tree*)malloc(sizeof(tree));
  tree->root = NULL;
  return tree;
}

Tree* BT_create_with_root (char value) {
  Tree* tree = (Tree*)malloc(sizeof(tree));
  tree->root = create_node(value);
  return tree;
}


void Node_destroy(Node* node) {
  Node* current = node;
  if (current != NULL) {
    if (current->left != NULL) {
      Node_destroy(current->left);
    }
    if (current->right != NULL) {
      Node_destroy(current->right);
    }
    free(current);
  }
}

void Tree_destroy (Tree* tree) {
  Node_destroy(tree->root);
  free(tree);
}
