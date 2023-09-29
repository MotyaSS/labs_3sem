#include <stdio.h>
#include "l1-4.h"
#include "..\my_flag_lib.h"


int main(int argc, char* argv[]) {
  switch (input(argc, argv)) {
    case TOO_FEW_ARGS:
      printf("Too few arguments\n");
      break;
    case FLAG_ERROR:
      printf("Not flag entered\n");
      break;
    case FLAG_UNKNOWN:
      printf("Flag is unknown\n");
      break;
    case FLAG_TOO_LONG:
      printf("Flag is way too long\n");
      break;
    case ARGC_ERROR:
      printf("Arguments count error\n");
      break;
    case OK:
      printf("All ok\n");
      break;
    case FILE_IS_NULL:
      printf("File error occurred\n");
      break;
    default:
      printf("Unknown status code\n");
  }
}
