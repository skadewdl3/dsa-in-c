#include <stdio.h>


void merge_sorted_arrays (int* array, int low, int mid, int high) {
  int left_length = mid - low + 1;
  int right_length = high - mid;

  int temp_left[left_length];
  int temp_right[right_length];

  int i = 0, j = 0, k = 0;

  for (int i = 0; i < left_length; i++) temp_left[i] = array[low + i];
  for (int j = 0; j < right_length; j++) temp_right[j] = array[mid + 1 + j];
  

  for (i = 0, j = 0, k = low; k <= high; k++) {
    if ((i < left_length) && (j >= right_length || temp_left[i] <= temp_right[j])) {
      array[k] = temp_left[i];
      i++;
    }
    else {
      array[k] = temp_right[j];
      j++;
    }
  }
}

void merge_sort_recursion (int* array, int low, int high) {
  if (low < high) {
    int mid = low + (high - low) / 2;
    merge_sort_recursion(array, low, mid);
    merge_sort_recursion(array, mid + 1, high);
    merge_sorted_arrays(array, low, mid, high);
  }
}

void merge_sort (int* array, int length) {
  merge_sort_recursion(array, 0, length - 1);
}

int main () {
  int array[] = {1, 5, 90, -1, 67, 0};
  int length = 6;

  merge_sort(array, length);
  for (int i = 0; i < length; i++) printf("%d ", array[i]);
}