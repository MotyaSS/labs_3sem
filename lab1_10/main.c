#include <stdio.h>
#include <stdlib.h>
#include "l1-10.h"


int main() {
  int cap = BUFSIZ;
  char* str = (char*) malloc(cap);
  long result = 0;
  find_max_from_input(&str, &cap, &result);
  for(int i = 9; i <= 36; i+= 9) {
    show_number_with_base(result, i);
  }
  free(str);
  return 0;
}
