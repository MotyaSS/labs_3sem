#include "l1-5.h"
#include "..\my_flag_lib.h"

int input(int argc, char* argv[]) {
  if (argc != 2)
    return ARGC_ERROR;
  if(!if_lf(argv[1]))
    return ARG_NOT_LF;
  return 0;
}