#include <stdarg.h>
#include <math.h>
#include "l2-2.h"

double rec_power(double exp, int power_it) {
  if (power_it == 1) {
    return exp;
  }
  if (power_it == 0) {
    return 1;
  }
  if ((power_it & 1) == 1) {
    return exp * rec_power(exp * exp, power_it >> 1);
  } else {
    return rec_power(exp * exp, power_it >> 1);
  }
}

int power(double num, int power, double* res) {

  int flag = 0;
  if (power < 0) {
    flag = 1;
    power = -power;
  }

  *res = rec_power(num, power);
  if (flag)
    *res = 1 / (*res);

  return 0;
}

int geometric_mean(double* res, int count, ...) {
  va_list ap;
  va_start(ap, count);
  double product = 1;
  for (int i = 0; i < count; ++i) {
    double temp = va_arg(ap, double);
    product *= temp;
  }
  va_end(ap);
  *res = pow(product, 1.0 / count);
  return 0;
}