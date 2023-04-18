#include <stdio.h>
#include "circular-linked-list/circular-linked-list.h"

int main()
{

  IntLL *list = IntLL_create();

  // list = LL_push(list, 1);
  // list = LL_push(list, 2);

  // LL_print(list);

  LL_push(list, 69);
  LL_push(list, 90);

  LL_insert(list, 70, 0);
  LL_insert(list, 70, 2);

  LL_print(list);
  // LL_delete(list, 1);

  LL_print(list);


  LL_destroy(list);

  return 0;
}