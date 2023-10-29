#include <stdio.h>
#include "l2-10.h"

int main() {
  double* coefs;
  int n = 4;
  if(tr_polynomial(n, 1, 1, &coefs, 5.0, 11.0, 3.0, 8.0) != ok){
    printf("Something is off\n");
    return 1;
  }
  for (int i = 0; i < n; i++){
    printf("%lf ", coefs[i]);
  }
  putchar('\n');
  return 0;
}
