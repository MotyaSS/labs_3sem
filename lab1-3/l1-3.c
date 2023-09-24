#include "l1-3.h"
#include "../my_flag_lib.h"


int flags() {

}

int input(int argc, char* argv[]) {
  if (argc < 2)
    return TOO_FEW_ARGS;
  if (!if_flag(argv[1])) {
    return FLAG_ERROR;
  }
  char* flag;
  return 0;
}