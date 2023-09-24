#include <string.h>
#include "l1-3.h"
#include "../my_flag_lib.h"

#define BUFF_SIZE 100

int flags_handling(char* flag, int argc, char* argv[]) {
  if (strcmp(flag, "q")) {
    if (argc != 6)
      return ARGC_ERROR;
  } else if (strcmp(flag, "m")) {
    if (argc != 4)
      return ARGC_ERROR;
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