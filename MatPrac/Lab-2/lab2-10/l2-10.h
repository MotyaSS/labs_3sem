#ifndef L2_10_H
#define L2_10_H

#include <stdlib.h>

typedef enum {
  ok,
  bad_alloc,
  inv_n,
  inv_eps
} st_code;

st_code tr_polynomial(size_t n, double x0, double eps, double** result_k, ...);

#endif