#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "l1-5.h"
#include "..\my_flag_lib.h"

int input(int argc, char* argv[]) {
  if (argc != 3)
    return ARGC_ERROR;

  if (!if_l(argv[1]))
    return INCORRECT_ARG;
  long x = strtol(argv[1], NULL, 10);

  if (!if_lf(argv[2]))
    return INCORRECT_ARG;
  double eps = strtod(argv[1], NULL);

  printf("%lf\n", sum_a(x, eps));
  printf("%lf\n", sum_b(x, eps));
  printf("%lf\n", sum_c(x, eps));
  printf("%lf\n", sum_d(x, eps));
  return 0;
}

double sum_a(long x, double eps) {
  long n = 1;
  double cur = x;
  double prev;
  do {
    n++;
    prev = cur;
    cur = prev * x / n;
  } while (fabs(cur - prev) > eps);
  return cur;
}

double sum_b(long x, double eps) {
  long n = 1;
  double cur = -1.0 * (x * x) / 2;
  double prev;
  do {
    n++;
    prev = cur;
    cur = -1 * prev * x / (2 * n + 1) * x / (2 * n + 2);
  } while (fabs(cur - prev) > eps);
  return cur;
}

double sum_c(long x, double eps) {

}

double sum_d(long x, double eps) {

}