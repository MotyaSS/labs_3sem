#include <stdio.h>
#include "../my_flag_lib.h"

enum {
  TOO_FEW_ARGS,
  FLAG_ERROR
};

int flags(){

}

int input(int argc, char* argv[]) {
  if (argc < 2)
    return TOO_FEW_ARGS;
  if (!if_flag(argv[1])) {
    return FLAG_ERROR;
  }

  return 0;
}

int main() {

}