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
  if (!if_lf(argv[2]) || !if_lf(argv[3]) || !if_lf(argv[4]) || !if_lf(argv[5]))
    return ARGUMENT_IR;
  double ans[6][2];
  int ans_errs[6];
  double first, second, third, epsilon;
  epsilon = strtod(argv[2], NULL);
  first = strtod(argv[3], NULL);
  second = strtod(argv[4], NULL);
  third = strtod(argv[5], NULL);
  int code = quadratic_eq(ans, ans_errs, first, second, third, epsilon);;
  for (int i = 0; i < 6; i++) {
    if (ans_errs[i] == -1) {
      continue;
    }
    if (ans_errs[i] == 0) {
      printf("%lf %lf\n", ans[i][0], ans[i][1]);
    }
  }
  return code;
}

int quadratic_eq(double ans[6][2], int ans_errs[6], double first, double second, double third, double eps) {
  ans_errs[0] = solve_quadr_eq(ans[0], first, second, third, eps);
  ans_errs[1] = solve_quadr_eq(ans[1], first, third, second, eps);
  ans_errs[2] = solve_quadr_eq(ans[2], second, third, first, eps);
  ans_errs[3] = solve_quadr_eq(ans[3], second, first, third, eps);
  ans_errs[4] = solve_quadr_eq(ans[4], third, first, second, eps);
  ans_errs[5] = solve_quadr_eq(ans[5], third, second, first, eps);
  return 0;
}

int solve_quadr_eq(double ans[2], double a, double b, double c, double eps) {
  double discr = b * b - 4 * a * c;
  if (fabs(discr) < eps) {
    ans[0] = (-b + sqrt(discr)) / (2 * a);
    ans[1] = ans[0];
    return 0;
  }
  if (discr < 0) {
    return -1;
  }
  ans[0] = (-b + sqrt(discr)) / (2 * a);
  ans[1] = (-b - sqrt(discr)) / (2 * a);
  return 0;
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

bool multiplicity(int first, int second) {

}

int t_fl_print(const int argc, const char* argv[]) {
  return 0;
}

bool triangle(double first, double second, double third, double eps) {

}

int flags_handling(char* flag, int argc, char* argv[]) {
  if (strcmp(flag, "q") == 0) {
    return q_fl_print(argc, argv);
  } else if (strcmp(flag, "m") == 0) {
    return m_fl_print(argc, argv);
  } else if (strcmp(flag, "t") == 0) {
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