#include <stdio.h>
#include "./ll.h"

int main () {
  Polynomial pow3 = Polynomial_create(5, 3);
  Polynomial pow1 = Polynomial_create(3, 1);
  Polynomial pow0 = Polynomial_create(3, 0);

  Polynomial pow3_ = Polynomial_create(5, 3);
  Polynomial pow2_ = Polynomial_create(3, 2);
  Polynomial pow1_ = Polynomial_create(3, 1);
  Polynomial pow0_ = Polynomial_create(3, 0);

  IntLL *poly1 = IntLL_create();
  IntLL_push(poly1, pow3);
  IntLL_push(poly1, pow1);
  IntLL_push(poly1, pow0);

  IntLL *poly2 = IntLL_create();
  IntLL_push(poly2, pow3_);
  IntLL_push(poly2, pow2_);
  IntLL_push(poly2, pow1_);
  IntLL_push(poly2, pow0_);

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

  for (int i = 0; i < result->length; i++) {
    Polynomial p = IntLL_get(result, i);
    printf("%dx^%d", p.coefficient, p.exponent);
    if (i != result->length - 1) {
      printf(" + ");
    }
  }

}