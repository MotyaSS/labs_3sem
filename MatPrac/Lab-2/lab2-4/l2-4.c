#include <stdarg.h>
#include <malloc.h>
#include "l2-4.h"

int make_vector(point2 A, point2 B, vector2* res) {
  res->x = B.x - A.x;
  res->y = B.y - A.y;
  return 0;
}

double rotation_val(vector2 vec1, vector2 vec2) {
  return (vec1.x * vec2.y - vec1.y * vec2.x);
}

int is_convex_polygon(unsigned int n, ...) {
  if (n < 3) {
    return -1;
  }
  if (n == 3) {
    return 1;
  }
  va_list ap;
  va_start(ap, n);
  point2 x1 = va_arg(ap, point2), x2 = va_arg(ap, point2);
  vector2 prev_vec, cur_vec;
  make_vector(x1, x2, &prev_vec);
  point2 start_point = x1;
  x1 = x2;
  x2 = va_arg(ap, point2);
  make_vector(x1, x2, &cur_vec);
  double rotation_prev, rotation_cur = rotation_val(prev_vec, cur_vec);
  for (int i = 3; i < n; i++) {
    x1 = x2;
    x2 = va_arg(ap, point2);

    prev_vec = cur_vec;
    make_vector(x1, x2, &cur_vec);

    rotation_prev = rotation_cur;
    rotation_cur = rotation_val(prev_vec, cur_vec);

    if (rotation_cur * rotation_prev <= 0) {
      va_end(ap);
      return 0;
    }
  }
  va_end(ap);
  x1 = x2;
  x2 = start_point;

  prev_vec = cur_vec;
  make_vector(x1, x2, &cur_vec);

  rotation_prev = rotation_cur;
  rotation_cur = rotation_val(prev_vec, cur_vec);

  if (rotation_cur * rotation_prev <= 0) {
    return 0;
  }

  return 1;
}

int n_pow_polynomial(double* res, double x, unsigned int n, ...) {

  double* factors = (double*) malloc(sizeof(double) * (n + 1));
  if(factors == NULL) {
    return -1;
  }

  va_list ap;
  va_start(ap, n);
  for (int i = 0; i < n + 1; i++) {
    factors[i] = va_arg(ap, double);
  }
  va_end(ap);

  double x_i_pow = 1;
  double sum_val = 0;
  for(int i = n; i >= 0; i--){
    sum_val += x_i_pow * factors[i];
    x_i_pow *= x;
  }
  *res = sum_val;
  free(factors);
  return 0;
}