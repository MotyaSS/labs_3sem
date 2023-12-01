#include <stdio.h>
#include "l4-7.h"


int main() {
  FILE* in = fopen("in.txt", "r");
  FILE* out = fopen("out.txt", "w");
  switch(parse_file(in, out)){
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
}
