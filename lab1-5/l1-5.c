#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "l1-5.h"
#include "..\my_flag_lib.h"

fsc input(int argc, char* argv[]) {
  if (argc != 3)
    return ARGC_ERROR;
  if (!if_lf(argv[1]))
    return INCORRECT_ARG;
  double x = strtod(argv[1], NULL);
  if (x <= 0)
    return INCORRECT_ARG;
  if (!if_lf(argv[2]))
    return INCORRECT_ARG;
  double eps = strtod(argv[2], NULL);
  double res;
  sum_a(x, eps, &res);
  printf("%lf\n", res);

  sum_b(x, eps, &res);
  printf("%lf\n", res);

  fsc status_code = sum_c(x, eps, &res);
  if (status_code == INCORRECT_ARG)
    printf("Enter x less than 1\n");
  else
    printf("%lf\n", res);
  status_code = sum_d(x, eps, &res);
  if (status_code == INCORRECT_ARG)
    printf("Enter x less (or equal) than 1\n");
  else
    printf("%lf\n", res);
  return OK;
}

fsc sum_a(double x, double eps, double* res) {
  long n = 0;
  double cur = 1;
  double sum = cur;
  double prev;
  do {
    n++;
    prev = cur;
    cur = prev * x / n;
    sum += cur;
  } while (fabs(cur) > eps);
  *res = sum;
  return OK;
}

fsc sum_b(double x, double eps, double* res) {
  long n = 0;
  double cur = 1;
  double sum = cur;
  double prev;
  do {
    prev = cur;
    cur = -1 * prev * x / (2 * n + 1) * x / (2 * n + 2);
    sum += cur;
    n++;
  } while (fabs(cur) > eps);
  *res = sum;
  return OK;
}

fsc sum_c(double x, double eps, double* res) {
  if (x >= 1)
    return INCORRECT_ARG;
  long n = 0;
  double cur = 1;
  //pow(3, 3) * x * x / (3 * 2)
  double sum = cur;
  double prev;
  do {
    prev = cur;
    cur = prev * pow(3 * (n + 1), 3) / (3 * n + 1) / (3 * n + 2) * x / (3 * n + 3) * x;
    sum += cur;
    n++;
  } while (fabs(cur) > eps);
  *res = sum;
  return OK;
}

fsc sum_d(double x, double eps, double* res) {
  if (x > 1)
    return INCORRECT_ARG;
  long n = 1;
  double cur = -1.0 * 1 * pow(x, 2) / 2;
  double sum = cur;
  double prev;
  do {
    prev = cur;
    cur = -1.0 * prev * (2 * n + 1) / (2 * n + 2) * pow(x, 2);
    sum += cur;
    n++;
  } while (fabs(cur) > eps);
  *res = sum;
  return OK;
}