#include <stdio.h>
#include "l1-3.h"

int main(int argc, char* argv[]) {
  switch (input(argc, argv)) {
    case ok:
      printf("all ok\n");
      break;
    case inv_argc:
      printf("invalid argc\n");
      break;
    case cant_open_infile:
      printf("inp file unknown\n");
      break;
    case cant_open_outfile:
      printf("can't open output file");
      break;
  }

  return 0;
}
