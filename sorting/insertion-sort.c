#include <stdio.h>

void insertion_sort (int* array, int length) {
  for (int i = 1; i < length; i++) {
    int j = i - 1;
    while (j >= 0 && array[j] > array[j + 1]) {
      int temp = array[j];
      array[j] = array[j + 1];
      array[j + 1] = temp;
      j--;
    }
  }
}

int main () {

  int length;
  scanf("%d%*c", &length);
  int array[length];
  for (int i = 0; i < length; i++) {
    scanf("%d%*c", &array[i]);
  }

  insertion_sort(array, length);
  for (int i = 0; i < length; i++) {
    printf("%d ", array[i]);
  }

}