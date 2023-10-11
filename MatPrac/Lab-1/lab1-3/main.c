#include <stdio.h>
#include "l1-3.h"

int main(int argc, char* argv[]) {
  switch (input(argc, argv)) {
    case TOO_FEW_ARGS:
      printf("Enter more arguments\n");
      break;
    case FLAG_ERROR:
      printf("Entered not a flag\n");
      break;
    case FLAG_TOO_LONG:
      printf("The flag is too long. Consider using less than BUFF_SIZE-length flag\n");
      break;
    case FLAG_UNKNOWN:
      printf("Flag is unknown\n");
      break;
    case ARGC_ERROR:
      printf("Argument count error\n");
      break;
    case INVALID_NUMBER:
      printf("Number entered incorrectly\n");
      break;
    default:
      printf("All went OK\n");
  }
  return 0;
}