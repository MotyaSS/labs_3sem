#include <stdio.h>
#include "l2-7.h"
#include "math.h"

double own(double x)
{
  return x * x - 2;
}

int main() {
  double res;
  dichotomy(&res, 1, 2, 1e-8, own);
  printf("%lf", res);
  return 0;
}
