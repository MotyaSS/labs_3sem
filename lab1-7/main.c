#include <stdio.h>
#include "l1-7.h"

int main(int argc, char* argv[]) {
  switch (input(argc, argv)) {
    case OK:
      printf("All Ok\n");
      break;
    case FILE_IS_NULL:
      printf("Unknown file\n");
      break;
    case INVALID_ARGC:
      printf("Invalid argument count\n");
      break;
    case NOT_FLAG:
      printf("Not flag entered\n");
      break;
    case UNKNOWN_FLAG:
      printf("Unknown flag\n");
      break;
    default:
      printf("Unknown status code\n");
  }
}
