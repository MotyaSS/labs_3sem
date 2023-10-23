#include "l2-8.h"

int main() {
  char* result;
  sum_base_n(4, 11, &result, "1231231", "Giant ho-...", "AAAAAA",  "A");
  free(result);
  return 0;
}
