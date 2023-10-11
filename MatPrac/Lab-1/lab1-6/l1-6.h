#ifndef L1_6_H
#define L1_6_H

typedef enum {
  OK,
  ARGC_INVALID,
  EPS_INVALID
} fsc;

fsc input(int argc, char* argv[]);
void print_all_integrals(double eps);

int integral_a(double eps, double* res);
int integral_b(double eps, double* res);
int integral_c(double eps, double* res);
int integral_d(double eps, double* res);

#endif