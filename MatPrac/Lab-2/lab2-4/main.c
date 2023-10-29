#include <stdio.h>
#include "l2-4.h"

int main() {
//  .______________.
//  |              |
//  |              |
//  |              |
//  |              |
//  .______________.


  point2 a, b, c, d;
  a.x = 1;
  a.y = 1;
  b.x = 1;
  b.y = 0;
  c.x = 0;
  c.y = 0;

  d.x = 0;
  d.y = 1;

  printf("%d\n", is_convex_polygon(4, a, b, c, d)); // 1 - yes, 0 - no, -1 - n invalid
  double f;
  n_pow_polynomial(&f, 2.2, 2, (double) 1, (double) 3, (double) 0);
  printf("%lf\n", f);
  return 0;
}