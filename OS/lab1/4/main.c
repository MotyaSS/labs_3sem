#include <stdio.h>
#include "l1-4.h"
int main(int argc, char* argv[]) {
  switch(input(argc, argv)){
    case ok:
      printf("all ok\n");
      break;
    case inv_argc:
      printf("invalid argc\n");
      break;
    case unknown_file:
      printf("unknown file\n");
      break;
    default:
      printf("unknown status code\n");
  }
  return 0;
}