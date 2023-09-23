#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "l1-2.h"
#define EPS_LOWER_BOUND 0.00000001
enum input_handle_err {
  invalid_argc = 1,
  invalid_eps
};

int input_handle(int argc, char* argv[]) {
  if (argc != 2) {
    return invalid_argc;
  }
  double eps;
  char* endptr = NULL;
  eps = strtod(argv[1], &endptr);
  if(endptr != (argv[1] + strlen(argv[1])) || eps < EPS_LOWER_BOUND) // endptr указывает после строки? || tiny eps
    return invalid_eps;

  print_all_e(eps);
  print_all_pi(eps);
  print_all_ln2(eps);
  print_all_sqrt2(eps);
  print_all_y(eps);
  return 0;
}

int main(int argc, char* argv[]) {
  input_handle(argc, argv);
  return 0;
}
