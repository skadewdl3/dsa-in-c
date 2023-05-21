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

int binary_search (int* array, int length, int key) {
  int low = 0;
  int high = length - 1;
  int mid;

  while (low <= high) {
    mid = (low + high) / 2;
    if (array[mid] == key) {
      return mid;
    } else if (array[mid] < key) {
      low = mid + 1;
    } else {
      high = mid - 1;
    }
  }
  return -1;
}

int main () {

  int length;
  int key;
  scanf("%d%*c", &length);
  int array[length];
  for (int i = 0; i < length; i++) {
    scanf("%d%*c", &array[i]);
  }
  scanf("%d%*c", &key);

  // bubble_sort(array, length);
  int index = binary_search(array, length, key);

  if (index == -1) {
    printf("absent\n");
  } else {
    printf("present at %d index\n", index);
  }

}