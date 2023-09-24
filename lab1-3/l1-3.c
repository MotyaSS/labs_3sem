#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "l1-3.h"
#include "../my_flag_lib.h"

#define BUFF_SIZE 100

int q_fl_print(const int argc, const char* argv[]) {
  if (argc != 6)
    return ARGC_ERROR;
  if (!if_lf(argv[2]) || !if_lf(argv[3]) || !if_lf(argv[4]) || !if_ll(argv[5]))
    return ARGUMENT_IR;
  double ans[6][3];
  double first, second, third, epsilon;
  epsilon = strtod(argv[2], NULL);
  first = strtod(argv[3], NULL);
  second = strtod(argv[4], NULL);
  third = strtod(argv[5], NULL);
  int code = quadratic_eq(ans, first, second, third, epsilon);;
  if (code == 0) {
    //some stuff
  }
  return code;
}

int quadratic_eq(double ans[6][2], double first, double second, double third, double eps) {
  solve_quadr_eq(ans[0], first, second, third, eps);
  solve_quadr_eq(ans[1], first, third, second, eps);
  solve_quadr_eq(ans[2], second, third, first, eps);
  solve_quadr_eq(ans[3], second, first, third, eps);
  solve_quadr_eq(ans[4], third, first, second, eps);
  solve_quadr_eq(ans[5], third, second, first, eps);
  return 0;

}

int solve_quadr_eq(double ans[2], double a, double b, double c, double eps) {
  double discr = b * b - 4 * a * c;
  if(fabs(discr) < eps){
    ans[0];
    ans[1];
  }
}

int m_fl_print(const int argc, const char* argv[]) {
  if (argc != 4)
    return ARGC_ERROR;
  if (!if_ll(argv[2]) || !if_ll(argv[3]))
    return ARGUMENT_IR;
  long long first = strtoll(argv[2], NULL, 10), second = strtoll(argv[3], NULL, 10);
  if (multiplicity(first, second))
    printf("OK, divisible\n");
  else
    printf("Not OK, not divisible\n");
  return 0;
}

int t_fl_print(const int argc, const char* argv[]) {
  return 0;
}

int flags_handling(char* flag, int argc, char* argv[]) {
  if (strcmp(flag, "q")) {
    return q_fl_print(argc, argv);
  } else if (strcmp(flag, "m")) {
    return m_fl_print(argc, argv);
  } else if (strcmp(flag, "t")) {
    if (argc != 6)
      return ARGC_ERROR;
  } else {
    return FLAG_UNKNOWN;
  }
  return 0;
}

int input(int argc, char* argv[]) {
  if (argc < 2)
    return TOO_FEW_ARGS;
  if (!if_flag(argv[1])) {
    return FLAG_ERROR;
  }
  char flag[BUFF_SIZE];
  if (strlen(argv[1]) >= BUFF_SIZE)
    return FLAG_TOO_LONG;
  strcpy_without_first(argv[1], flag);
  return flags_handling(flag, argc, argv);
}