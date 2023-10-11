#include <stdio.h>
#include "l1-3.h"

st_code input(int argc, char* argv[]) {
  if (argc != 3) {
    return inv_argc;
  }
  FILE* in = fopen(argv[1], "rb");
  if (in == NULL) {
    return cant_open_infile;
  }
  FILE* out = fopen(argv[2], "wb");
  if (out == NULL) {
    return cant_open_outfile;
  }

  copy_file(in, out);
  fclose(in);
  fclose(out);
  return ok;
}

int copy_file(FILE* src, FILE* dest) {
  char buff[BUFSIZ];
  size_t a = fread(buff, sizeof(char), BUFSIZ, src);
  while (a > 0) {
    fwrite(buff, sizeof(char), a, dest);
    a = fread(buff, sizeof(char), 1, src);
  }
  return 0;
}