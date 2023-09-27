#include <stdio.h>
#include "l1-5.h"

int main(int argc, char* argv[]) {
  switch (input(argc, argv)) {
    case ARGC_ERROR:
      printf("Incorrect argument count\n");
      break;
    case INCORRECT_ARG:
      printf("Incorrect argument entered\n");
      break;
    default:
      printf("All ok\n");
  }
}
