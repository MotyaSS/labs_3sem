#include <stdio.h>
#include <malloc.h>
#include "l3-1.h"

char get_digit(unsigned int val) {
  return val < 10 ? val + '0' : val + 'A' - 10;
}

void show_num(int const* num) {
  while (*num != -1) {
    putchar(get_digit(*(num++)));
  }
  putchar('\n');
}

int main() {
  int* result;
  if(base10_to_base_2pow_r(511, 3, &result) == 0) {
    show_num(result);
    free(result);
  }
  if(base10_to_base_2pow_r(511, 5, &result) == 0) {
    show_num(result);
    free(result);
  }
  if(base10_to_base_2pow_r(10, 1, &result) == 0) {
    show_num(result);
    free(result);
  }
}
