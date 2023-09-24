#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "l1-3.h"
#include "../my_flag_lib.h"

#define BUFF_SIZE 100

typedef enum{
  DISCRIMINANT_OK,
  DISCRIMINANT_LESS_ZERO = -1
}quadr_st_codes;

int q_fl_print(const int argc, const char* argv[]) {
  if (argc != 6)
    return ARGC_ERROR;
  if (!if_lf(argv[2]) || !if_lf(argv[3]) || !if_lf(argv[4]) || !if_lf(argv[5]))
    return ARGUMENT_IR;
  double ans[6][2];
  quadr_st_codes ans_errs[6];
  double first, second, third, epsilon;
  epsilon = strtod(argv[2], NULL);
  first = strtod(argv[3], NULL);
  second = strtod(argv[4], NULL);
  third = strtod(argv[5], NULL);
  int code = quadratic_eq(ans, ans_errs, first, second, third, epsilon);;
  for (int i = 0; i < 6; i++) {
    if (ans_errs[i] == DISCRIMINANT_LESS_ZERO) {
      continue;
    }
    if (ans_errs[i] == DISCRIMINANT_OK) {
      printf("%lf %lf\n", ans[i][0], ans[i][1]);
    }
  }
  return code;
}

bool abc_unique(double a, double b, double c, const double unique[3]) {
  if (a == unique[0] && b == unique[1] && c == unique[2])
    return false;
  return true;
}

int quad_unique_add(double ans[6][2], int ans_errs[6], double a, double b, double c, double eps, double unique[6][3],
                    int* len) {
  for (int i = 0; i < *len; i++) {
    if (!abc_unique(a, b, c, unique[i]))
      return -1;
  }
  ans_errs[*len] = solve_quadr_eq(ans[*len], a, b, c, eps);
  unique[*len][0] = a, unique[*len][1] = b, unique[*len][2] = c;
  (*len)++;
  return 0;
}

int quadratic_eq(double ans[6][2], int ans_errs[6], double first, double second, double third, double eps) {
  double ans_unique[6][3];
  int len = 0;
  quad_unique_add(ans, ans_errs, first, second, third, eps, ans_unique, &len);
  quad_unique_add(ans, ans_errs, first, third, second, eps, ans_unique, &len);
  quad_unique_add(ans, ans_errs, second, third, first, eps, ans_unique, &len);
  quad_unique_add(ans, ans_errs, second, first, third, eps, ans_unique, &len);
  quad_unique_add(ans, ans_errs, third, first, second, eps, ans_unique, &len);
  quad_unique_add(ans, ans_errs, third, second, first, eps, ans_unique, &len);
  return 0;
}

int solve_quadr_eq(double ans[2], double a, double b, double c, double eps) {
  double discr = b * b - 4 * a * c;
  if (fabs(discr) < eps) {
    ans[0] = (-b + sqrt(discr)) / (2 * a);
    ans[1] = ans[0];
    return DISCRIMINANT_OK;
  }
  if (discr < 0) {
    return DISCRIMINANT_LESS_ZERO;
  }
  ans[0] = (-b + sqrt(discr)) / (2 * a);
  ans[1] = (-b - sqrt(discr)) / (2 * a);
  return DISCRIMINANT_OK;
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