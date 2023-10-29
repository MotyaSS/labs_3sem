#include "l2-10.h"
#include <stdarg.h>

st_code calc_polynomial(double x0, double* coefs, size_t n, double* res) {
  *res = 0;
  for (int i = 0; i <= n; ++i) {
    *res *= x0;
    *res += coefs[n - i];
  }
  return ok;
}

st_code calc_differ(double* coefs, size_t n, int iter) {
  for (int j = 0; j < n - iter; j++) {
    coefs[j] = (j + 1) * coefs[j + 1];
  }
  coefs[n - iter] = 0;
  return ok;
}


st_code tr_polynomial(size_t n, double x0, double eps, double** result_k, ...) {
  if (n == 0) {
    return inv_n;
  }

  if (eps <= 0) {
    return inv_eps;
  }

  double* inp_k = (double*) malloc(sizeof(double) * n);
  if (inp_k == NULL) {
    return bad_alloc;
  }
  *result_k = (double*) malloc(sizeof(double) * n);
  if (result_k == NULL) {
    free(inp_k);
    return bad_alloc;
  }
  va_list a;
  va_start(a, result_k);
  for (int i = 0; i < n; i++) {
    inp_k[i] = va_arg(a, double);
  }
  va_end(a);

  for (int i = 0; i < n; i++) {
    // считаем коэффицеинты

    calc_polynomial(x0, inp_k, n - i, &((*result_k)[i]));

    //деление на факториал
    for (int j = 2; j < i + 1; j++) {
      (*result_k)[i] /= j;
    }

    //дифференцируем для следуюшего шага
    calc_differ(inp_k, n, i);
  }

  free(inp_k);
  return ok;
}