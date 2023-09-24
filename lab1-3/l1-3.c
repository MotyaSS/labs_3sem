#include "l1-3.h"
#include "../my_flag_lib.h"
#define BUFF_SIZE 100

int flags(char* flag) {
  return 0;
}

int input(int argc, char* argv[]) {
  if (argc < 2)
    return TOO_FEW_ARGS;
  if (!if_flag(argv[1])) {
    return FLAG_ERROR;
  }
  char flag[BUFF_SIZE];
  strcpy_without_first(argv[1], flag);
  return 0;
}