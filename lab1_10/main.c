#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "l1-10.h"

typedef enum {
  OK,
  INCORRECT_STRING,
  INVALID_BASE
} myf_sc;

bool if_lowercase_in_string(const char* string) {
  for (int i = 0; string[i] != '\0'; i++) {
    if (string[i] >= 'a' && string[i] <= 'z') {
      return false;
    }
  }
  return true;
}

myf_sc my_func(char** string, int* cap) {
  get_string_safely_realloc(string, cap, stdin);
  char* endptr;
  long base = strtol(*string, &endptr, 10);
  if (endptr != *string + strlen(*string)) {
    return INCORRECT_STRING;
  }
  if (base < 2 || base > 36) {
    return INVALID_BASE;
  }

  get_string_safely_realloc(string, cap, stdin);
  long num;
  long max_ = LONG_MIN;
  do {
    if (!if_lowercase_in_string(*string)) {
      continue;
    }
    num = strtol(*string, &endptr, base);
    if (endptr != *string + strlen(*string)) {
      continue;
    }
    max_ = num > max_ ? num : max_;
    get_string_safely_realloc(string, cap, stdin);
  } while (strcmp(*string, "Stop") != 0);
  return OK;
}

int main() {
  int cap = BUFSIZ;
  char* str = (char*) malloc(cap);
  my_func(&str, &cap);
  free(str);
  return 0;
}
