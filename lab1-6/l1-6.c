#include "l1-6.h"
#include <stdlib.h>
#include <stdio.h>
#include "../my_flag_lib.h"

fsc input(int argc, char* argv[]) {
  if (argc != 2) {
    return ARGC_INVALID;
  }
  if (!if_lf(argv[1])) {
    return EPS_INVALID;
  }
  double eps = strtod(argv[1], NULL);
  print_all_integrals(eps);
  return OK;
}

void print_all_integrals(double eps) {
  double a,b,c,d;
  integral_a(eps, &a);
  integral_b(eps, &b);
  integral_c(eps, &c);
  integral_d(eps, &d);
  printf("A: %lf\nB: %lf\nC: %lf\nD: %lf\n", a, b, c, d);
}

int integral_a(double eps, double* res) {

}

int integral_b(double eps, double* res) {

}

int integral_c(double eps, double* res) {

}

int integral_d(double eps, double* res) {

}