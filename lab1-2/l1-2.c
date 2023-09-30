#include "l1-2.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define EPS_LOWER_BOUND 0.00000001


st_code input_handle(int argc, char* argv[]) {
  if (argc != 2) {
    return INVALID_ARGC;
  }
  double eps;
  char* endptr = NULL;
  eps = strtod(argv[1], &endptr);
  if (endptr != (argv[1] + strlen(argv[1])) || eps < EPS_LOWER_BOUND) { // endptr указывает после строки? || tiny eps
    return INVALID_EPS;
  }
  print_all_e(eps);
  print_all_pi(eps);
  print_all_ln2(eps);
  print_all_sqrt2(eps);
  print_all_y(eps);
  return INPUT_OK;
}

calc_st_code print_all_e(double eps) {
  double lim_res, sum_res, equ_res;
  calc_st_code a = e_lim(eps, &lim_res);
  e_sum(eps, &sum_res);
  e_equation(eps, &equ_res);
  if (a != OK) {
    printf("lim is not ok\n");
    return a;
  }
  printf("%.10lf %.10lf %.10lf\n", lim_res, sum_res, equ_res);
  return OK;
}

calc_st_code e_lim(double eps, double* result) {
  double cur = 0, prev;
  long n = 1;
  do {
    prev = cur;
    cur = pow((1 + 1.0 / n), n); //влоб (?)
    if (n < LONG_MAX / 2) {
      n *= 2;
    } else {
      return LIM_NOT_OK;
    }
  } while (fabs(cur - prev) > eps);
  *result = cur;
  return OK;
}

calc_st_code e_sum(double eps, double* result) {
  double cur = 0, prev;
  long n = 1;
  double n_fact = 1;
  do {
    prev = cur;
    cur = prev + n_fact;
    n_fact /= (1.0 * n++);
  } while (fabs(cur - prev) > eps);
  *result = cur;
  return OK;
}

calc_st_code e_equation(double eps, double* result) {
  double left = 2.0, right = 3.0, mid = 0;
  double cur, prev;
  do {
    prev = mid;
    mid = (left + right) / 2;
    cur = log(mid);

    if (cur >= 1) {
      right = mid;
    } else {
      left = mid;
    }
  } while (fabs(prev - mid) > eps);
  *result = mid;
  return OK;
}

calc_st_code print_all_pi(double eps) {
  double lim_res, sum_res, equ_res;
  pi_lim(eps, &lim_res);
  pi_sum(eps, &sum_res);
  pi_equation(eps, &equ_res);

  printf("%.10lf %.10lf %.10lf\n", lim_res, sum_res, equ_res);
  return OK;
}

calc_st_code pi_lim(double eps, double* result) {  // :-(
  double cur = pow(2, 4) / pow(2, 2), prev;
  long n = 1;
  do {
    prev = cur;
    cur = prev * n;
    cur /= pow(2 * n + 1, 2);
    cur *= pow(2, 4) * pow(n + 1, 3);
    cur /= pow(2 * n + 2, 2);
    n++;
  } while (fabs(cur - prev) > eps);
  *result = cur;
  return OK;
}


calc_st_code pi_sum(double eps, double* result) {
  double cur = 1;
  long n = 1;
  double sum = cur;
  do {
    n++;
    cur = 1.0 * (n % 2 == 0 ? -1 : 1) / (2 * n - 1);
    sum += cur;
  } while (fabs(cur) > eps);
  *result = 4 * sum;
  return OK;
}

calc_st_code pi_equation(double eps, double* result) {
  double left = 3, right = 3.5, mid;
  double cur;
  do {
    mid = (right + left) / 2;
    cur = sin(mid);
    if (cur > 0) {
      left = mid;
    } else {
      right = mid;
    }
  } while (fabs(left - right) > eps);
  *result = mid;
  return OK;
}

calc_st_code print_all_ln2(double eps) {
  double lim_res, sum_res, equ_res;
  calc_st_code a = ln2_lim(eps, &lim_res);
  ln2_sum(eps, &sum_res);
  ln2_equation(eps, &equ_res);
  if (a != OK) {
    printf("lim is not ok\n");
    return a;
  }
  printf("%.10lf %.10lf %.10lf\n", lim_res, sum_res, equ_res);
  return OK;
}

calc_st_code ln2_lim(double eps, double* result) {
  double cur = 0, prev;
  long n = 1;
  do {
    prev = cur;
    cur = n * (pow(2, 1.0 / n) - 1);
    if (n < LONG_MAX / 2) {
      n *= 2;
    } else {
      return LIM_NOT_OK;
    }
  } while (fabs(cur - prev) > eps);
  *result = cur;
  return OK;
}

calc_st_code ln2_sum(double eps, double* result) {
  double cur = 1;
  long n = 1;
  double sum = cur;
  do {
    n++;
    cur = -1.0 * (n % 2 == 0 ? 1 : -1) / n;
    sum += cur;
  } while (fabs(cur) > eps);
  *result = sum;
  return OK;
}

calc_st_code ln2_equation(double eps, double* result) {
  double left = 0, right = 1, mid;
  double cur;
  do {
    mid = (right + left) / 2;
    cur = exp(mid);
    if (cur > 2) {
      right = mid;
    } else {
      left = mid;
    }
  } while (fabs(left - right) > eps);
  *result = mid;
  return OK;
}

calc_st_code print_all_sqrt2(double eps) {
  double lim_res, sum_res, equ_res;
  calc_st_code a = sqrt2_lim(eps, &lim_res);
  sqrt2_sum(eps, &sum_res);
  sqrt2_equation(eps, &equ_res);
  if (a != OK) {
    printf("lim is not ok\n");
    return a;
  }
  printf("%.10lf %.10lf %.10lf\n", lim_res, sum_res, equ_res);
  return OK;
}

calc_st_code sqrt2_lim(double eps, double* result) {
  double cur = 0.5, prev;
  do {
    prev = cur;
    cur = prev - pow(prev, 2) / 2 + 1;
  } while (fabs(cur - prev) > eps);
  *result = cur;
  return OK;
}

calc_st_code sqrt2_sum(double eps, double* result) {

  return OK;
}

calc_st_code sqrt2_equation(double eps, double* result) {

  return OK;
}


calc_st_code print_all_y(double eps) {

  return OK;
}

calc_st_code y_lim(double eps, double* result) {

  return OK;
}

calc_st_code y_sum(double eps, double* result) {

  return OK;
}

calc_st_code y_equation(double eps, double* result) {

  return OK;
}