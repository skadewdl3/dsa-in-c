#include <stdio.h>

void selection_sort (int* array, int length) {
  for (int i = 0; i < length; i++) {
    int min_index = i;
    for (int j = i; j < length; j++) {
      if (array[j] < array[min_index]) {
        min_index = j;
      }
    }
    int temp = array[i];
    array[i] = array[min_index];
    array[min_index] = temp;
  }
}

int main () {

  int length;
  int key;
  scanf("%d%*c", &length);
  int array[length];
  for (int i = 0; i < length; i++) {
    scanf("%d%*c", &array[i]);
  }

  selection_sort(array, length);
  for (int i = 0; i < length; i++) {
    printf("%d ", array[i]);
  }

}