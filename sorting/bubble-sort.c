#include <stdio.h>

void bubble_sort (int* array, int length) {
  for (int i = 0; i < length; i++) {
    int swaps = 0;
    for (int j = 1; j < length - i; j++) {
      if (array[j] < array[j - 1]) {
        int temp = array[j];
        array[j] = array[j - 1];
        array[j - 1] = temp;
        swaps++;
      }
    }
    if (swaps == 0) break;
  }
}

int main () {

  int length;
  scanf("%d%*c", &length);
  int array[length];
  for (int i = 0; i < length; i++) {
    scanf("%d%*c", &array[i]);
  }

  bubble_sort(array, length);
  for (int i = 0; i < length; i++) {
    printf("%d ", array[i]);
  }

}