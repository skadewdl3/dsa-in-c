#include <stdio.h>

int linear_search (int* array, int length, int key) {
  for (int i = 0; i < length; i++) {
    if (array[i] == key) {
      return i;
    }
  }
  return -1;
}

int main () {


  int array[] = {1, 2, 3, 4, 5, 6, 7, 8};
  int length = 8;
  int key = 7;

  int index = linear_search(array, length, key);

  if (index == -1) {
    printf("Key not found\n");
  } else {
    printf("Key found at index %d\n", index);
  }

}