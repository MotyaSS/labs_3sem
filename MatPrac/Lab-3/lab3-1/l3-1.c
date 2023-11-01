#include <malloc.h>
#include "l3-1.h"

int base10_to_base_2pow_r(unsigned long long num, unsigned int r, int** result) {
  if (r < 1 || r > 5) {
    return 1;
  }
  int cnt = 0;
  if (num == 0) {
    cnt = 1;
  }

  unsigned long long t_n = num;
  while (t_n) {
    cnt++;
    t_n >>= r;
  }

  *result = (int*) malloc(sizeof(int) * (cnt + 1));
  if(*result == NULL){
    return -1;
  }

  for (int i = cnt - 1; i >= 0; i--) {
    unsigned int t = num >> r;
    t <<= r;
    (*result)[i] = t ^ num;
    num >>= r;
  }
  (*result)[cnt] = -1;

  return 0;
}