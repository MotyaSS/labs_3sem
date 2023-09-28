#include "l1-2.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int print_all_e(double eps) {
  double lim_res, sum_res, equ_res;
  int a = e_lim(eps, &lim_res);
  int b = e_sum(eps, &sum_res);
  int c = e_equation(eps, &equ_res);
  if (a != 0) {
    printf("lim is not ok\n");
    return a;
  }
  printf("%.10lf %.10lf %.10lf\n", lim_res, sum_res, equ_res);
  return 0;
}

int e_lim(double eps, double* result) {
  double cur = 0, prev;
  long long n = 1;
  do {
    prev = cur;
    cur = pow((1 + 1.0 / n), n); //влоб (?)
    if (n < LONG_LONG_MAX / 2)
      n *= 2;
    else
      return -1; // err code
  } while (fabs(cur - prev) > eps);
  *result = cur;
  return 0;
}

int e_sum(double eps, double* result) {
  double cur = 0, prev;
  long long n = 1;
  double n_fact = 1;
  do {
    prev = cur;
    cur = prev + n_fact;
    n_fact /= (1.0 * n++);
  } while (fabs(cur - prev) > eps);
  *result = cur;
  return 0;
}

int e_equation(double eps, double* result) {
  double left = 2.0, right = 3.0, mid = 0;
  double cur = 0, prev;
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
  return 0;
}

int print_all_pi(double eps) {
  double lim_res, sum_res, equ_res;
  int a = pi_lim(eps, &lim_res);
  int b = pi_sum(eps, &sum_res);
  int c = pi_equation(eps, &equ_res);

  printf("%.10lf %.10lf %.10lf\n", lim_res, sum_res, equ_res);
  return 0;
}

int pi_lim(double eps, double* result) {  // :-(
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
  return 0;
}


int pi_sum(double eps, double* result) {
  double cur = 1;
  long n = 1;
  double sum = cur;
  do {
    n++;
    cur = 1.0 * (n % 2 == 0 ? -1 : 1) / (2 * n - 1);
    sum += cur;
  } while (fabs(cur) > eps);
  *result = 4 * sum;
  return 0;
}

int pi_equation(double eps, double* result) {
  double left = 3, right = 3.5, mid;
  double cur = 0;
  do {
    mid = (right + left) / 2;
    cur = sin(mid);
    if(cur > 0)
      left = mid;
    else
      right = mid;
  } while (fabs(left - right) > eps);
  *result = mid;
  return 0;
}

int print_all_ln2(double eps) {
  double lim_res, sum_res, equ_res;
  int a = ln2_lim(eps, &lim_res);
  int b = ln2_sum(eps, &sum_res);
  int c = ln2_equation(eps, &equ_res);

  printf("%.10lf %.10lf %.10lf\n", lim_res, sum_res, equ_res);
  return 0;
}

int ln2_lim(double eps, double* result) {

}

int ln2_sum(double eps, double* result) {

}

int ln2_equation(double eps, double* result) {

}

int print_all_sqrt2(double eps) {

}

int sqrt2_lim(double eps, double* result) {

}

int sqrt2_sum(double eps, double* result) {

}

int sqrt2_equation(double eps, double* result) {

}


int print_all_y(double eps) {

}

int y_lim(double eps, double* result) {

}

int y_sum(double eps, double* result) {

}

int y_equation(double eps, double* result) {

}