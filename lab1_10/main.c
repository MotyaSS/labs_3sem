#include <stdio.h>
#include "l1-10.h"

int main(int argc, char* argv[]) {
  switch (input(argc, argv)) {
    case OK:
      printf("All ok\n");
      break;
    case INVALID_FILE:
      printf("File unknown\n");
      break;
    case INVALID_ARGC:
      printf("Invalid argument count\n");
      break;
    default:
      printf("Unknown status code\n");
  }
  return 0;
}
