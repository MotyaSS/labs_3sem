#include "l1-1.h"

int main(int argc, char* argv[]) {
  switch (input(argc, argv)) {
    case ok:
      break;
    case inv_argc:
      printf("invalid argc\n");
      break;
    case cant_open_file:
      printf("couldn't open file\n");
      break;
    default:
      printf("stc unknown\n");
  }
  return 0;
}
