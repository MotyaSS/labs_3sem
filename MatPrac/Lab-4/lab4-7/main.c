#include <stdio.h>
#include "l4-7.h"


int main(int argc, char** argv) {
  if (argc < 0) {
    printf("Invalid argc\n");
    return -1;
  }
  FILE* in = fopen(argv[0], "r");
  if (!in) {
    printf("Invalid input file\n");
    return -1;
  }
  FILE* out = fopen(argv[1], "w");
  if (!out) {
    fclose(in);
    printf("Invalid output file\n");
    return -1;
  }
  switch (parse_file(in, out)) {
    case parse_rv_ok:
      printf("all ok\n");
      break;
    case parse_rv_uninit:
      printf("uninitialized variable used\n");
      break;
    case parse_rv_bad_alloc:
      printf("bad alloc\n");
      break;
    case parse_rv_inv:
      printf("something is invalid in input\n");
  }
  fclose(in);
  fclose(out);
  return 0;
}
