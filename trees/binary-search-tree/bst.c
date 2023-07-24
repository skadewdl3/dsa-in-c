#include <stdio.h>
#include <stdlib.h>


typedef struct BSTNode {
  int value;
  int is_null;
  struct BSTNode* left;
  struct BSTNode* right;
} Node;

typedef struct {
  Node* root;
} BST;


void traverse_nodes_preorder (Node* node) {
  if (node != NULL) {
    printf("%d ", node->value);
    if (!node->left->is_null) {
      traverse_nodes_preorder(node->left);
    }
    if (!node->right->is_null) {
      traverse_nodes_preorder(node->right);
    }
  }

}

void traverse_nodes_inorder (Node* node) {
  if (node != NULL) {
    if (!node->left->is_null) {
      traverse_nodes_inorder(node->left);
    }
    printf("%d ", node->value);
    if (!node->right->is_null) {
      traverse_nodes_inorder(node->right);
    }
  }

}

Node* create_empty_bst_node () {
  Node* node = (Node*)malloc(sizeof(Node));
  node->value = -1;
  node->is_null = 1;
  node->right = NULL;
  node->left = NULL;
}

Node* create_bst_node (int value) {
  Node* node = (Node*)malloc(sizeof(Node));
  node->value = value;
  node->is_null = 0;
  node->right = create_empty_bst_node();
  node->left = create_empty_bst_node();
  return node;
}

BST* create_binary_search_tree () {
  BST* bst = (BST*)malloc(sizeof(BST));
  bst->root = NULL;
  return bst;
}

void bst_insert (BST* tree, int value) {
  if (tree->root == NULL) {
    tree->root = create_bst_node(value);
    return;
  }
  Node* current = tree->root;
  while (1) {
    // printf("\n%d %d", current->is_null, value);
    if (current->is_null) {
      current->value = value;
      current->left = create_empty_bst_node();
      current->right = create_empty_bst_node();
      current->is_null = 0;
      break;
    }
    else {
      if (value < current->value) {
        current  = current->left;
      }
      else {
        current = current->right;
      }
    }
  }
}



int main () {
  BST* bst = create_binary_search_tree();
  bst_insert(bst, 1);
  bst_insert(bst, 2);
  bst_insert(bst, 3);
  bst_insert(bst, 4);
  bst_insert(bst, 5);
  bst_insert(bst, 6);
  bst_insert(bst, 7);
  bst_insert(bst, -1);
  bst_insert(bst, 98);

  traverse_nodes_preorder(bst->root);
}