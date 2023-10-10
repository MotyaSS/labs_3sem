#ifndef OS_L1_3_H
#define OS_L1_3_H

typedef enum {
  ok,
  inv_argc,
  cant_open_infile,
  cant_open_outfile
} st_code;

st_code input(int argc, char* argv[]);
int copy_file(FILE* src, FILE* dest);
#endif