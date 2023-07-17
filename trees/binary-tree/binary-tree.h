#include <stdio.h>
#include <stdlib.h>

typedef enum {
  INORDER, PREORDER, POSTORDER
} TraversalTypes;

typedef struct TreeNode {
  int value;
  struct TreeNode* left;
  struct TreeNode* right;
} Node;

typedef struct {
  int depth;
  Node* root;
} Tree;

typedef struct {
  int* data;
  int length;
  TraversalTypes type;
} Serialized;

Serialized* Serialized_init (TraversalTypes type) {
  Serialized* serialized = (Serialized*)malloc(sizeof(Serialized));
  serialized->data = NULL;
  serialized->length = 0;
  serialized->type = type;
  return serialized;
}

void Serialized_print (Serialized* serialized) {
  for (int i = 0; i < serialized->length; i++) {
    if (serialized->data[i] != INT_MIN) {
      printf("%d ", serialized->data[i]);
    }
    else {
      printf("NULL ");
    }
  }
  
}

void Serialized_push (Serialized* serialized, int value) {
  if (serialized->data == NULL) {
    serialized->data = (int*)malloc(sizeof(int));
    serialized->data[0] = value;
    serialized->length = 1;
  }
  else {
    serialized->data = realloc(serialized->data, (serialized->length + 1) * sizeof(int));
    serialized->data[serialized->length] = value;
    serialized->length += 1;
  }
}

Node* create_node (int value) {
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

Tree* BT_create_with_root (int value) {
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


Serialized* serialize_preorder (Tree* tree) {

  Serialized* serialized = Serialized_init(PREORDER);

  void traverse_nodes_preorder (Node* node) {
    if (node == NULL) {
      Serialized_push(serialized, INT_MIN);
    }
    else {
      Serialized_push(serialized, node->value);
      traverse_nodes_preorder(node->left);
      traverse_nodes_preorder(node->right);
    }
  }

  traverse_nodes_preorder(tree->root);

  return serialized;
}

Serialized* serialize_inorder (Tree* tree) {

  Serialized* serialized = Serialized_init(INORDER);

  void traverse_nodes_inorder (Node* node) {
    if (node == NULL) {
      Serialized_push(serialized, INT_MIN);
    }
    else {
      traverse_nodes_inorder(node->left);
      Serialized_push(serialized, node->value);
      traverse_nodes_inorder(node->right);
    }
  }

  traverse_nodes_inorder(tree->root);

  return serialized;
}

Serialized* serialize_postorder (Tree* tree) {

  Serialized* serialized = Serialized_init(INORDER);

  void traverse_nodes_postorder (Node* node) {
    if (node == NULL) {
      Serialized_push(serialized, INT_MIN);
    }
    else {
      traverse_nodes_postorder(node->left);
      traverse_nodes_postorder(node->right);
      Serialized_push(serialized, node->value);
    }
  }

  traverse_nodes_postorder(tree->root);

  return serialized;
}

Serialized* serialize (Tree* tree, TraversalTypes type) {
  switch (type) {
    case PREORDER:
      serialize_preorder(tree);
      break;
    case INORDER:
      serialize_inorder(tree);
      break;
    case POSTORDER:
      serialize_postorder(tree);
      break;
  }
}


Tree* deserialize_preorder (Serialized* serialized) {
  int index = 0;
  Node* deserialize_recursion (Serialized* serialized) { 
    if (serialized->length == index) {
      return NULL;
    }
    if (serialized->data[index] == INT_MIN) {
      index++;
      return NULL;
    }
    Node* new_node = create_node(serialized->data[index]);
    index++;
    new_node->left = deserialize_recursion(serialized);
    new_node->right = deserialize_recursion(serialized);
    return new_node;
  }
  
  Tree* tree = BT_create();
  tree->root = deserialize_recursion(serialized);
  return tree;
}

Tree* deserialize_postorder (Serialized* serialized) {
  int index = serialized->length - 1;
  Node* deserialize_recursion (Serialized* serialized) { 
    if (index == -1) {
      return NULL;
    }
    if (serialized->data[index] == INT_MIN) {
      index--;
      return NULL;
    }
    Node* new_node = create_node(serialized->data[index]);
    index--;
    new_node->right = deserialize_recursion(serialized);
    new_node->left = deserialize_recursion(serialized);
    return new_node;
  }
  
  Tree* tree = BT_create();
  tree->root = deserialize_recursion(serialized);
  return tree;
}

Tree* deserialize (Serialized* serialized) {
  switch (serialized->type) {
    case PREORDER:
      deserialize_preorder(serialized);
      break;
    case INORDER:
      break;
    case POSTORDER:
      deserialize_postorder(serialized);
      break;
  }
}