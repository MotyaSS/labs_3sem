#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "..\my_flag_lib.h"
#include "l1-1.h"

int main(int argc, char* argv[]) {
  int code = my_func(argc, argv);
  switch (code) {
    case ARGUMENTS_COUNT_IR:
      printf("Argument count is irrelevant\n");
      break;
    case FLAG_ISSUE:
      printf("Flag issue detected\n");
      break;
    case NOT_NUMBER:
      printf("Not a number\n");
      break;
    case H_NO_SUCH_NUMBERS:
      printf("No such numbers\n");
      break;
    case E_MORE_THAN_TEN:
      printf("Number is more than ten\n");
      break;
    case E_NON_POSITIVE:
      printf("Number is not positive\n");
      break;
    case A_NEGATIVE:
      printf("Number is negative, sum is 0\n");
      break;
    case A_MORE_THAN_LLMAX:
      printf("Sum is too huge\n");
      break;
    case F_MORE_THAN_LLMAX:
      printf("Factorial is too huge\n");
      break;
    case FLAG_UNDEF:
      printf("Undefined flag\n");
      break;
    default:
      printf("All went ok\n");
  }
  return 0;
}