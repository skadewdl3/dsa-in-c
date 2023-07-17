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

  Serialized* serialized = serialize(tree, POSTORDER);
  Serialized_print(serialized);

  Tree* deserialized = deserialize(serialized);
  printf("\n%d\n", tree->root->value);
  traverse_postorder(deserialized);

}