#ifndef L2_4_H
#define L2_4_H

typedef struct point2__ {
  double x;
  double y;
} point2;

typedef struct vector2__ {
  double x;
  double y;
} vector2;

int make_vector(point2 A, point2 B, vector2* res);

int is_convex_polygon(unsigned int n, ...);

int n_pow_polynomial(double* res, double x, unsigned int n, ...);

#endif