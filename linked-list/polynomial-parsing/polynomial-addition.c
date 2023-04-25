#include <stdio.h>
#include "./ll.h"

int main () {

  int num_terms1 = 0;
  int num_terms2 = 0;

  IntLL *poly1 = IntLL_create();
  IntLL *poly2 = IntLL_create();


  printf("\nEnter degree of poly1: ");
  scanf("%d", &num_terms1);

  for (int i = 0; i <= num_terms1; i++) {
    int coeff;
    printf("Enter coefficient of x^%d: ", num_terms1 - i);
    scanf("%d", &coeff);
    IntLL_push(poly1, Polynomial_create(coeff, num_terms1 - i));
  }

  
  printf("\nEnter degree of poly2: ");
  scanf("%d", &num_terms2);

  for (int i = 0; i <= num_terms2; i++) {
    int coeff;
    printf("Enter coefficient of x^%d: ", num_terms2 - i);
    scanf("%d", &coeff);
    IntLL_push(poly2, Polynomial_create(coeff, num_terms2 - i));
  }

  IntLL *greater = poly2->length > poly1->length ? poly2 : poly1;
  IntLL *lesser = poly2->length > poly1->length ? poly1 : poly2;

  IntLL *result = IntLL_create();


  for (int i = 0; i < greater->length; i++) {
    int added = 0;
    Polynomial g = IntLL_get(greater, i);
    for (int j = 0; j < lesser->length; j++) {
      Polynomial l = IntLL_get(lesser, j);
      if (g.exponent > l.exponent) {
        break;
      }
      if (g.exponent == l.exponent) {
        IntLL_push(result, Polynomial_create(g.coefficient + l.coefficient, g.exponent));
        added = 1;
        break;
      }
    }
    if (!added) {
      IntLL_push(result, g);
    }
  }

  printf("\n");
  for (int i = 0; i < result->length; i++) {
    Polynomial p = IntLL_get(result, i);
    printf("%dx^%d", p.coefficient, p.exponent);
    if (i != result->length - 1) {
      printf(" + ");
    }
  }

}