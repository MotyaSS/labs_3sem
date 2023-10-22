#include <stdio.h>
#include "l2-7.h"
#include "math.h"
int main() {
  double res;
  dichotomy(&res, 0, 3.14, 0.1, cos);
  printf("%lf", res);
  return 0;
}
