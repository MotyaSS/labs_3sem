#include <malloc.h>
#include <stdio.h>
#include "l2-9.h"

void print_arr(int const* arr, size_t count) {
  for (int i = 0; i < count; i++) {
    printf("%s ", arr[i] ? "yes" : "no");
  }
  putchar('\n');
}

int main() {
  int* result;
  if (check_base_multiple_nums(&result, 4, 5, (double) 0.2, (double) 0.4, (double) 0.3, (double) 0.24) == 0) {
    print_arr(result, 4);
    free(result);
  }

  if (check_base_multiple_nums(&result, 4, 2, (double) 0.2, (double) 0.4, (double) 0.3, (double) 0.24) == 0) {
    print_arr(result, 4);
    free(result);
  }

  if (check_base_multiple_nums(&result, 4, 10, (double) 0.125, (double) 0.625, (double) 0.5, (double) 0.25) == 0) {
    print_arr(result, 4);
    free(result);
  }

  return 0;
}