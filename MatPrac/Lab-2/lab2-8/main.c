#include "l2-8.h"

int main() {
  char* result;
  sum_base_n(3, 16, &result, "00000000000", "FF", "1");
  free(result);
  return 0;
}
