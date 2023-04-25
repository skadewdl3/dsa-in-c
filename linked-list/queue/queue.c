#include <stdio.h>
#include "./queue-int.h"

int main () {
  Queue *q = Queue_create();
  Queue_enqueue(q, 10);
  Queue_enqueue(q, 11);
  Queue_enqueue(q, 12);
  Queue_print(q);
  Queue_destroy(q);
}