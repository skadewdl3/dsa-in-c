#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int* values;
  int length;
} Array;

Array* Array_create () {
  Array* arr = malloc()
}

int* partition () {

}

int* merge (int* ) {

}


void merge_sort (int* arr, int low, int high) {
  int mid = (low + high) / 2;

  int* c = partition(arr, low, mid);
  int* d = partition(arr, mid + 1, high);

  merge(c, d)

}

int main () {

  int arr[] = {90, 8, 76, -2, 3, 7};
  int length = 6;

  merge_sort (arr, 0, length - 1);

}