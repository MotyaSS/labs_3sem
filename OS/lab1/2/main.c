#include "l1-2.h"
#include <stdio.h>

int main() {
  struct tm t;
  int a = parse_date(&t);
//  start_app();
  printf("%d", a);
  return 0;
}