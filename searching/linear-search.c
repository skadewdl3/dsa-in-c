#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int count;
  int* values;
} Result;

Result* linear_search (int* array, int length, int key) {
  Result* result = malloc(sizeof(Result));
  result->count = 0;
  result->values = NULL;

  for (int i = 0; i < length; i++) {
    if (array[i] == key) {
      if (result->count == 0) {
        result->values = malloc(sizeof(int));
      } else {
        result->values = realloc(result->values, sizeof(int) * (result->count + 1));
      }
      result->values[result->count] = i;
      result->count++;
    }
  }
  return result;
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


  Result* result = linear_search(array, length, key);

  if (result->count == 0) {
    printf("absent\n");
  }
  else {
    for (int i = 0; i < result->count; i++) {
      printf("present at %d position\n", result->values[i] + 1);
    }
  }

}