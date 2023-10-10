#include <stdio.h>
#include <stdlib.h>
#include "l1-10.h"


int main() {
  int cap = BUFSIZ;
  char* str = (char*) malloc(cap);
  long result = 0;
  switch ((find_max_from_input(&str, &cap, &result))) {
    case INVALID_BASE:
      printf("Invalid base\n");
      return -1;
    case INCORRECT_STRING:
      printf("Incorrect entered base\n");
      return -1;
    case OK:
      printf("Base OK\n");
      break;
    default:
      printf("Unknown status code\n");
      return -1;
  }
  for(int i = 9; i <= 36; i+= 9) {
    show_number_with_base(result, i);
  }
  free(str);
  return 0;
}
