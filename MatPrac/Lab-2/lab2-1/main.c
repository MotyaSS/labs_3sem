#include <stdio.h>
#include "l2-1.h"

int main(int argc, char* argv[]) {
  char* str = "rat";
  char res[4];
  str_reverse(str, res);
  printf("%s\n", res);
  switch (input(argc, argv)) {
    case ok:
      printf("all ok\n");
      break;
    case inv_flag:
      printf("invalid flag\n");
      break;
    case inv_argc:
      printf("invalid argc\n");
      break;
    case inv_num:
      printf("invalid number\n");
      break;
    case unknown_flag:
      printf("unknown flag\n");
      break;
    default:
      printf("unknown st code\n");
  }
  return 0;
}
