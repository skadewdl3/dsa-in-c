#include <stdio.h>
#include "circular-linked-list/circular-linked-list.h"

int main()
{

  IntLL *list = IntLL_create();

  list = LL_push(list, 1);
  list = LL_push(list, 2);

  LL_print(list);

  printf("%d", list->head->next->next->value);

  LL_destroy(list);

  return 0;
}