#include <stdlib.h>
#include <string.h>
#include "l1-3.h"
#include "../my_flag_lib.h"

#define BUFF_SIZE 100

int q_fl(const int argc, const char* argv[]) {
  if (argc != 6)
    return ARGC_ERROR;
  if (!if_lf(argv[2]) || !if_lf(argv[3]) || !if_lf(argv[4]) || !if_ll(argv[5]))
    return ARGUMENT_IR;
  double ans[6][3];
  double first, second, third, epsilon;
  epsilon = strtod(argv[2], NULL);
  first = strtod(argv[3], NULL);
  second = strtod(argv[4], NULL);
  third = strtod(argv[5], NULL);
  return quadratic_eq(ans, first, second, third, epsilon);;
}

int m_fl(const int argc, const char* argv[]) {
  return 0;
}

int t_fl(const int argc, const char* argv[]) {
  return 0;
}

int flags_handling(char* flag, int argc, char* argv[]) {
  if (strcmp(flag, "q")) {
    return q_fl(argc, argv);
  } else if (strcmp(flag, "m")) {
    if (argc != 4)
      return ARGC_ERROR;
    if (!if_ll(argv[2]) || !if_ll(argv[3]))
      return ARGUMENT_IR;
  } else if (strcmp(flag, "t")) {
    if (argc != 6)
      return ARGC_ERROR;
  } else {
    return FLAG_UNKNOWN;
  }
  return 0;
}

int input(int argc, char* argv[]) {
  if (argc < 2)
    return TOO_FEW_ARGS;
  if (!if_flag(argv[1])) {
    return FLAG_ERROR;
  }
  char flag[BUFF_SIZE];
  if (strlen(argv[1]) >= BUFF_SIZE)
    return FLAG_TOO_LONG;
  strcpy_without_first(argv[1], flag);
  return flags_handling(flag, argc, argv);
}