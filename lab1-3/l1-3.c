#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "l1-3.h"
#include "../my_flag_lib.h"

#define BUFF_SIZE 100

typedef enum {
  DISCRIMINANT_OK,
  DISCRIMINANT_LESS_ZERO = -1
} quadr_st_codes;

st_code q_fl_print(const int argc, char* argv[]) {
  if (argc != 6) {
    return ARGC_ERROR;
  }
  if (!if_lf(argv[2]) || !if_lf(argv[3]) || !if_lf(argv[4]) || !if_lf(argv[5])) {
    return INVALID_NUMBER;
  }
  double ans[6][2];
  quadr_st_codes ans_errs[6];
  double first, second, third, epsilon;
  epsilon = strtod(argv[2], NULL);
  epsilon = fabs(epsilon);
  first = strtod(argv[3], NULL);
  second = strtod(argv[4], NULL);
  third = strtod(argv[5], NULL);
  int code = quadratic_eq_all_solves(ans, ans_errs, first, second, third, epsilon);
  return code;
}

bool if_abc_unique(double a, double b, double c, const double unique[3]) {
  return !(a == unique[0] && b == unique[1] && c == unique[2]);
}

int quad_unique_add(double ans[6][2], int ans_errs[6], double a, double b, double c, double eps,
                    double comb_unique[6][3], int* len) {
  for (int i = 0; i < *len; i++) {
    if (!if_abc_unique(a, b, c, comb_unique[i])) {
      return -1;
    }
  }
  ans_errs[*len] = solve_quadr_eq(ans[*len], a, b, c, eps);
  comb_unique[*len][0] = a, comb_unique[*len][1] = b, comb_unique[*len][2] = c;
  (*len)++;
  return 0;
}

int quadratic_eq_all_solves(double ans[6][2], int ans_errs[6], double first, double second, double third, double eps) {
  double comb_unique[6][3];
  int len = 0;
  quad_unique_add(ans, ans_errs, first, second, third, eps, comb_unique, &len);
  quad_unique_add(ans, ans_errs, first, third, second, eps, comb_unique, &len);
  quad_unique_add(ans, ans_errs, second, third, first, eps, comb_unique, &len);
  quad_unique_add(ans, ans_errs, second, first, third, eps, comb_unique, &len);
  quad_unique_add(ans, ans_errs, third, first, second, eps, comb_unique, &len);
  quad_unique_add(ans, ans_errs, third, second, first, eps, comb_unique, &len);
  for (int i = 0; i < len; i++) {
    if (ans_errs[i] == DISCRIMINANT_LESS_ZERO) {
      continue;
    }
    if (ans_errs[i] == DISCRIMINANT_OK) {
      printf("%lf %lf\n", ans[i][0], ans[i][1]);
    }
  }

  return 0;
}

int solve_quadr_eq(double ans[2], double a, double b, double c, double eps) {
  double discr = b * b - 4 * a * c;
  if (fabs(discr) < eps) {
    discr = 0;
  } else if (discr < -eps) {
    return DISCRIMINANT_LESS_ZERO;
  }
  ans[0] = (-b + sqrt(discr)) / (2 * a);
  ans[1] = (-b - sqrt(discr)) / (2 * a);
  return DISCRIMINANT_OK;
}

st_code m_fl_print(int argc, char* argv[]) {
  if (argc != 4) {
    return ARGC_ERROR;
  }
  if (!if_ll(argv[2]) || !if_ll(argv[3])) {
    return INVALID_NUMBER;
  }
  long long first = strtoll(argv[2], NULL, 10), second = strtoll(argv[3], NULL, 10);
  if (multiplicity(first, second)) {
    printf("OK, divisible\n");
  } else {
    printf("Not OK, not divisible\n");
  }
  return OK;
}

bool multiplicity(long long first, long long second) {
  return first % second == 0;
}

st_code t_fl_print(const int argc, char* argv[]) {
  if (argc != 6) {
    return ARGC_ERROR;
  }
  if (!if_lf(argv[2]) || !if_lf(argv[3]) || !if_lf(argv[4]) || !if_lf(argv[5])) {
    return INVALID_NUMBER;
  }
  double first, second, third, epsilon;
  epsilon = strtod(argv[2], NULL);
  first = strtod(argv[3], NULL);
  second = strtod(argv[4], NULL);
  third = strtod(argv[5], NULL);
  if (triangle(first, second, third, epsilon)) {
    printf("Triangle - OK\n");
  } else {
    printf("Triangle - not OK");
  }
  return OK;
}

double max(double a, double b) {
  return a > b ? a : b;
}

double min(double a, double b) {
  return a < b ? a : b;
}

bool triangle(double a, double b, double c, double eps) {
  double max_ = max(a, max(b, c));
  double min_ = min(a, min(b, c));
  double mid_ = a - max_ + b - min_ + c;
  return fabs(max_ * max_ - mid_ * mid_ - min_ * min_) < eps;
}

st_code flags_handling(char* flag, int argc, char* argv[]) {
  if (strcmp(flag, "q") == 0) {
    return q_fl_print(argc, argv);
  } else if (strcmp(flag, "m") == 0) {
    return m_fl_print(argc, argv);
  } else if (strcmp(flag, "t") == 0) {
    return t_fl_print(argc, argv);
  } else {
    return FLAG_UNKNOWN;
  }
}

st_code input(int argc, char* argv[]) {
  if (argc < 2) {
    return TOO_FEW_ARGS;
  }
  if (!if_flag(argv[1])) {
    return FLAG_ERROR;
  }
  char flag[BUFF_SIZE];
  if (strlen(argv[1]) >= BUFF_SIZE) {
    return FLAG_TOO_LONG;
  }
  strcpy_without_first(argv[1], flag);
  return flags_handling(flag, argc, argv);
}