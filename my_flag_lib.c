#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "my_flag_lib.h"

bool if_flag(const char arg[]) {
  if (arg == NULL)
    return false;
  if (arg[0] != '-' && arg[0] != '/') {
    return false;
  }
  return true;
}

bool if_ll(const char arg[]) {
  char temp1[80];
  if (strlen(arg) >= 80)
    return false;

  char* temp2;
  strcpy(temp1, arg);
  temp2 = temp1;
  int len = strlen(arg);
  if (arg[0] == '-') {
    temp2 = temp1 + 1;
    len--;
  }

  long long number = 0;
  for (int i = 0; i < len; i++) {
    if (temp2[i] < '0' || temp2[i] > '9')
      return false;
    if (number > LONG_LONG_MAX / 10)
      return false;
    if (number == (LONG_LONG_MAX / 10) && (temp2[i] - '0') > (LONG_LONG_MAX % 10))
      return false;
    number *= 10;
    number += temp2[i] - '0';
  }
  return true;
}

bool if_lf(const char arg[]) {
  char* endptr = NULL;
  double res = strtod(arg, &endptr);
  if (endptr == arg + strlen(arg))
    return true;
  return false;
}

void strcpy_without_first(const char cpy[], char var[]) {
  if (cpy == NULL)
    return;
  strcpy(var, (cpy + 1));
}
