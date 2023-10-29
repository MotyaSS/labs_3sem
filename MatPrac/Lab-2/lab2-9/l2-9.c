#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include "l2-9.h"

double m_eps() {
  int i = 0;
  double eps = 1.0;

  while (1.0f + eps > 1.0f) {
    eps = eps / 2.0f;
    i++;
  }
  return eps;
}

int check_base_multiple_nums(int count, unsigned int base, ...) {
  va_list a;
  va_start(a, base);
  double eps = m_eps();
  for (int i = 0; i < count; i++) {
    double temp = va_arg(a, double);
    printf("%.10lf - %s, ", temp, check_base(temp, base, eps) ? "yes" : "no");
  }
  putchar('\n');
  va_end(a);
  return 0;
}

unsigned long long gcd(unsigned long long a, unsigned long long b) {
  if (a % b == 0) {
    return b;
  }
  if (b % a == 0) {
    return a;
  }
  if (a > b) {
    return gcd(a % b, b);
  }
  return gcd(a, b % a);
}

bool check_base(double num, unsigned int base, double eps) {
  if (base < 2) {
    return 0;
  }
  if (num <= 0 || num >= 1) {
    return 0;
  }

  eps = m_eps();
  unsigned long long denom = 1, numer = 1;
  while (fabs(num - floor(num)) >= eps) {
    denom *= 10;
    num *= 10;
    numer = floor(num);
  }
  denom = denom / gcd(denom, numer);

  unsigned int t_base = base;
  while (t_base < denom) {
    t_base *= base;
  }

  if (t_base == denom) {
    return true;
  }

  return false;
}