#include <stdio.h>
#include <stdlib.h>

/*
Bucket Sort Algorithm:
1. Decide a range or accept number of buckets from the user.
2. Range for buckets: 0.1 - 0.19, 0.2 - 0.29, 0.3 - 0.39, 0.4 - 0.49 ... 0.8 - 0.89, 0.9 - 0.99
*/

typedef struct {
  float min;
  float max;
  float* values;
  int count;
} Bucket;

Bucket *Bucket_create (float min, float max) {
  Bucket *b = (Bucket*)malloc(sizeof(Bucket));
  b->min = min;
  b->max = max;
  b->values = NULL;
  b->count = 0;
  return b;
}

void Bucket_add (Bucket* b, float value) {
  if (b->count == 0) {
    b->values = (float*)malloc(sizeof(float));
  }
  else {
    b->values = realloc(b->values, sizeof(float) * (b->count + 1));
  }
  b->values[b->count] = value;
  b->count++;
}

void Bucket_destroy (Bucket *b) {
  free(b);
}

void Bucket_sort (Bucket *b) {
  for (int i = 0; i < b->count; i++) {
    for (int j = 1; j < b->count - i; j++) {
      if (b->values[j] < b->values[j - 1]) {
        float temp = b->values[j - 1];
        b->values[j - 1] = b->values[j];
        b->values[j] = temp;
      }
    }
  }
}

void Bucket_print (Bucket *b) {
  printf("%f to %f: ", b->min, b->max);
  for (int i = 0; i < b->count; i++) {
    printf("%f ", b->values[i]);
  }
  printf("\n");
}

void distribute (float* values, int length, Bucket** buckets, int bucket_count) {
    for (int i = 0; i < length; i++) {
      int low = 0;
      int high = bucket_count;
      int mid = (low + high) / 2;
      float value = values[i];
        
      while (low <= high) {
        if (value < buckets[mid]->min) {
          high = mid;
          mid = (low + high) / 2;
        }
        else if (value > buckets[mid]->max) {
          low = mid;
          mid = (low + high) / 2;
        }
        else {
          Bucket_add(buckets[mid], value);
          break;
        }
      }
    }
    
}

float *combine (Bucket** buckets, int bucket_count, int length) {
  float* result = (float*)malloc(sizeof(float) * length);

  int k = 0;

  for (int i = 0; i < bucket_count; i++) {
    for (int j = 0; j < buckets[i]->count; j++) {
      result[k] = buckets[i]->values[j];
      k++;
    }
  }
  return result;
}

float get_max () {

}

int main () {

  // get values from user
  int arr_length = 0;
  printf("Enter number of elements to sort: ");
  scanf("%d%*c", &arr_length);
  printf("\n");
  float* arr = (float*)malloc(sizeof(float) * arr_length);
  for (int i = 0; i < arr_length; i++) {
    scanf("%f%*c", &arr[i]);
  }

  for (int i = 0; i < arr_length; i++) {
    printf("%f ", arr[i]);
  }

  float global_min = 0;
  float global_max = 0;
  printf("\n");
  printf("Enter min. element: ");
  scanf("%f%*c", &global_min);
  printf("\n");
  printf("Enter max. element: ");
  scanf("%f%*c", &global_max);
  printf("\n");
  float range = global_max - global_min;

  
  int bucket_count = 0;
  float prev_max = global_min;
  printf("Enter number of buckets: ");
  scanf("%d%*c", &bucket_count);
  printf("\n");

  Bucket** buckets = NULL; 
  for (int i = 0; i < bucket_count; i++) {
    float min = prev_max;
    float max = global_max / (bucket_count - i);
    if (i == 0) {
      buckets = (Bucket**)malloc(sizeof(Bucket*));
    }
    else {
      buckets = (Bucket**)realloc(buckets, sizeof(Bucket*) * (i + 1));
    }
    buckets[i] = Bucket_create(min, max);
    prev_max = max;
  }

  
  // distrbiyte values into buckets
  distribute(arr, arr_length, buckets, bucket_count);


  // sort individual buckets
  for (int i = 0; i < bucket_count; i++) {
    Bucket_sort(buckets[i]);
  }
  
  // combine all buckets
  float* result = combine(buckets, bucket_count, arr_length);

  // print result
  printf("Sorted values: ");
  for (int i = 0; i < arr_length; i++) {
    printf("%f ", result[i]);
  }

}