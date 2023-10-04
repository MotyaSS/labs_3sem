#include <stdio.h>
#include <stdlib.h>
#include "l1-10.h"

int main() {
  int cap = 2;
  char* str = (char*)malloc(cap);
  get_string_safely_realloc(&str, &cap,stdin);
  printf("%s", str);
}
