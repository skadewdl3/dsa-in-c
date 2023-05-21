#include <stdio.h>

void swap (int* x, int* y) {
  int temp = *x;
  *x = *y;
  *y = temp;
}

int partition (int* arr, int low, int high) {
  int pivot = arr[high];

  int i = low;

  for (int j = low; j < high; j++) {
    if (arr[j] <= pivot) {
      swap(&arr[i], &arr[j]);
      i++;
    }
  } 

  swap (&arr[i], &arr[high]);

  return i;
}

void quick_sort_recursion (int* arr, int low, int high) {
  if (low < high) {
    int pivot_index = partition(arr, low, high);
    quick_sort_recursion(arr, low, pivot_index - 1);
    quick_sort_recursion(arr, pivot_index + 1, high);
  }
}

void quick_sort (int* arr, int length) {
  quick_sort_recursion(arr, 0, length - 1);
}

int main () {
  int arr[] = {1, 5, 90, -1, 67, 0};
  int length = 6;
  quick_sort(arr, length);
  for (int i = 0; i < length; i++) printf("%d ", arr[i]);
}