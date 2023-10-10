#ifndef _L1_5_H_
#define _L1_5_H_

typedef enum {
  OK = 0,
  ARGC_ERROR,
  INCORRECT_ARG,
  EPS_NON_POSITIVE
} fsc;
fsc input(int argc, char* argv[]);
fsc sum_a(double x, double eps, double* res);
fsc sum_b(double x, double eps, double* res);
fsc sum_c(double x, double eps, double* res);
fsc sum_d(double x, double eps, double* res);

#endif