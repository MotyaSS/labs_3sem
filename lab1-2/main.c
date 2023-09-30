#include <stdio.h>
#include "l1-2.h"


int main(int argc, char* argv[]) {
  switch (input_handle(argc, argv)) {
    case INVALID_ARGC:
      printf("Invalid arg count\n");
      break;
    case INVALID_EPS:
      printf("Invalid epsilon\n");
      break;
    case INPUT_OK:
      printf("All ok\n");
      break;
    default:
      printf("Unknown status code\n");
  }
  return 0;
}
