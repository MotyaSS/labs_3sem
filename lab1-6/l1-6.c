#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "l1-6.h"
#include "../my_flag_lib.h"


fsc input(int argc, char* argv[]) {
  if (argc != 2) {
    return ARGC_INVALID;
  }
  if (!if_lf(argv[1])) {
    return EPS_INVALID;
  }
  double eps = strtod(argv[1], NULL);
  if(eps >= 1 || eps <= 0) {
    return EPS_INVALID;
  }
  print_all_integrals(eps);
  return OK;
}

void print_all_integrals(double eps) {
  double a, b, c, d;
  integral_a(eps, &a);
  integral_b(eps, &b);
  integral_c(eps, &c);
  integral_d(eps, &d);
  printf("A: %.10lf\nB: %.10lf\nC: %.10lf\nD: %.10lf\n", a, b, c, d);
}

double machine_eps() {
  int i = 0;
  double epsilon = 1.0;


  while (1.0f + epsilon > 1.0f) {
    epsilon = epsilon / 2.0f;
    i++;
  }
  return epsilon;
}

int integral_a(double eps, double* res) {
  double left = 0;
  double right = 1;
  double step = 1;
  double cur = 0;
  double prev = 0;

  do {
    step /= 2;
    double sum = 0;
    double point = left + step;
    double rectangle;
    prev = cur;
    double m_eps = machine_eps();

    while (fabs(point - right) >= m_eps) {
      rectangle = step * (log(1 + point) / point);
      sum += rectangle;
      point += step;
    }
    cur = sum;
  } while (fabs(cur - prev) > eps);
  *res = cur;
  return 0;
}

int integral_b(double eps, double* res) {
  double left = 0;
  double right = 1;
  double step = 1;
  double cur = 0;
  double prev = 0;
  double m_eps = machine_eps();
  do {
    step /= 2;
    double sum = 0;
    double point = left + step;
    double rectangle;
    prev = cur;
    while (fabs(point - right) >= m_eps) {
      rectangle = step * (exp(-point * point / 2));
      sum += rectangle;
      point += step;
    }
    cur = sum;
  } while (fabs(cur - prev) > eps);
  *res = cur;
  return 0;
}

int integral_c(double eps, double* res) {
  double left = 0;
  double right = 1;
  double step = 1;
  double cur = 0;
  double prev = 0;
  double m_eps = machine_eps();
  do {
    step /= 2;
    double sum = 0;
    double point = left;
    double right_lim = right;
    double rectangle;
    prev = cur;
    while (right_lim - point >= m_eps) {
      rectangle = step * (log(1.0 / (1 - point)));
      sum += rectangle;
      point += step;
    }
    cur = sum;
  } while (fabs(cur - prev) > eps);

  *res = cur;
  return 0;
}

int integral_d(double eps, double* res) {
  double left = 0;
  double right = 1;
  double step = 1;
  double cur = 0;
  double prev = 0;
  double m_eps = machine_eps();

  do {
    step /= 2;
    double sum = 0;
    double point = left;
    double rectangle;
    prev = cur;
    while (fabs(point - right) >= m_eps) {
      rectangle = step * (pow(point, point));
      sum += rectangle;
      point += step;
    }
    cur = sum;
  } while (fabs(cur - prev) > eps);
  *res = cur;
  return 0;
}