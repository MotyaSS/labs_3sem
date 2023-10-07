#include <stdio.h>
#include "l1-6.h"

int main(int argc, char* argv[]) {
  switch (input(argc, argv)) {
    case ARGC_INVALID:
      printf("Invalid argument count\n");
      break;
    case EPS_INVALID:
      printf("Invalid epsilon\n");
      break;
    case OK:
      printf("All ok\n");
      break;
    default:
      printf("Undefined status code\n");
  }
  return 0;
}
