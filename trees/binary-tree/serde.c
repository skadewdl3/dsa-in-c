#include <stdio.h>
#include "./binary-tree.h"

void traverse_nodes_preorder (Node* node) {
  if (node != NULL) {
    printf("%d", node->value);
    if (node->left != NULL) {
      traverse_nodes_preorder(node->left);
    }
    if (node->right != NULL) {
      traverse_nodes_preorder(node->right);
    }
  }

}

void traverse_preorder (Tree* tree) {
  traverse_nodes_preorder(tree->root);
}


void traverse_nodes_postorder (Node* node) {
  if (node != NULL) {
    if (node->left != NULL) {
      traverse_nodes_postorder(node->left);
    }
    if (node->right != NULL) {
      traverse_nodes_postorder(node->right);
    }
    printf("%d", node->value);
  }

}

void traverse_postorder (Tree* tree) {
  traverse_nodes_postorder(tree->root);
}

int main () {

  int pre_repr[] = {1, 2, 4, 7, NONE, 9, NONE, NONE, NONE, 5, NONE, NONE, 3, NONE, 6, NONE, 8, NONE, NONE };
  int post_repr[] = {NONE, NONE, NONE, 9, 7, NONE, 4, NONE, NONE, 5, 2, NONE, NONE, NONE, NONE, 8, 6, 3, 1};
  Tree* tree = deserialize(create_serialization(post_repr, 19, POSTORDER));

  Serialized* post_ser = serialize(tree, POSTORDER);
  Serialized_print(post_ser);
}

