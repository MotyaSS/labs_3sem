#include <stdio.h>
#include "l2-2.h"

int main() {
  double res;
  geometric_mean(&res, 4, (double) 2, (double) 4, (double) 8, (double) 64);
  printf("%lf\n", res);
  power(5, 1000, &res);
  printf("%lf\n", res);
}