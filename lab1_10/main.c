#include <stdio.h>
#include <stdlib.h>
#include "l1-10.h"

int main() {
  smart_string string;
  string.capacity = BUFSIZ;
  string.len = 0;
  string.str = (char*)malloc(BUFSIZ);
  get_string_safely_realloc(&string, stdin);
  printf("%s", string.str);
}
