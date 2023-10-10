#ifndef OS_L1_1_H
#define OS_L1_1_H

#include <stdio.h>

typedef enum {
  ok,
  inv_argc,
  cant_open_file
} st_code;
int print_all_file(FILE* stream);
int print_n_bytes_from_file(FILE* stream, int n);
int fill_file(char* buf, FILE* stream);
st_code execute(char* filename);
st_code input(int argc, char* argv[]);

#endif