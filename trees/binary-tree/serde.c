#include <stdio.h>
#include "./binary-tree.h"

int main () {

  int pre_repr[] = {1, 2, 4, 7, NONE, 9, NONE, NONE, NONE, 5, NONE, NONE, 3, NONE, 6, NONE, 8, NONE, NONE };
  int post_repr[] = {NONE, NONE, NONE, 9, 7, NONE, 4, NONE, NONE, 5, 2, NONE, NONE, NONE, NONE, 8, 6, 3, 1};
  Tree* tree = deserialize(create_serialization(post_repr, 19, POSTORDER));

  traverse(tree, PREORDER);
  printf("\n%d", height(tree));
}

