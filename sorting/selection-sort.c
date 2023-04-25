#include <stdio.h>

void selection_sort (int* array, int length) {
  for (int i = 0; i < length; i++) {
    int min_index = i;
    for (int j = i; j < length; j++) {
      if (array[j] < array[min_index]) {
        min_index = j;
      }
    }
    if (min_index == i) break;
    int temp = array[i];
    array[i] = array[min_index];
    array[min_index] = temp;
  }
}

int main () {

  int array[] = {1, 4, 5, 0, -1, 29, 67};
  int length = 7;

  selection_sort(array, length);
  for (int i = 0; i < length; i++) {
    printf("%d ", array[i]);
  }

}