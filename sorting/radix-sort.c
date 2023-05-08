#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
   int num_digits;
   int* digits;
} Element;

Element *Element_create (int num) {
  int copy = num;
  Element *element = (Element*)malloc(sizeof(Element));
  element->num_digits = 0;
  if (copy == 0) {
    element->num_digits = 1;
    element->digits = (int*)malloc(sizeof(int));
    element->digits[0] = copy;
  }
  while (copy > 0) {
    if (element->num_digits == 0) {
      element->digits = (int*)malloc(sizeof(int));
    }
    else {
      element->digits = (int*)realloc(element->digits, sizeof(int) * (element->num_digits + 1));
    }
    element->digits[element->num_digits] = copy % 10;
    copy /= 10;
    element->num_digits++;
  }
  return element;
}

void print_digits (Element* element, char delimiter) {
  for (int i = element->num_digits - 1; i >= 0; i--) {
    printf("%d", element->digits[i]);
  }
  printf("%c", delimiter);
}

int main () {

  int arr[] = {0, 170, 45, 6, 90, 802, 24, 2, 66};
  int arr_length  = 8;
  
  Element** elements = (Element**)malloc(sizeof(Element*) * arr_length);
  for (int i = 0; i < arr_length; i++) {
    Element *element = Element_create(arr[i]);
    elements[i] = element;
  }

  int total_passes = elements[0]->num_digits;
  int num_passes = 0;
  

  while (num_passes != total_passes) {


    for (int i = 0; i < arr_length; i++) {
      if (elements[i]->num_digits > total_passes) {
        total_passes = elements[i]->num_digits;
      }
      
      for (int j = 1; j < arr_length; j++) {
      Element* element = elements[j - 1];
      Element* next_element = elements[j];

      int n1 = element->num_digits > num_passes ? element->digits[num_passes] : 0;
      int n2 = next_element->num_digits > num_passes ? next_element->digits[num_passes] : 0;

        if (n1 > n2) {
          Element* temp = next_element;
          elements[j] = element;
          elements[j - 1] = temp;
        }
      }


    }
    num_passes++;
  }

  for (int i = 0; i < arr_length; i++) {
    print_digits(elements[i], ' ');
  }

}