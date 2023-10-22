#ifndef OS_L1_4_H
#define OS_L1_4_H

#include <stdio.h>

typedef unsigned char byte;
typedef unsigned int byte4;
typedef unsigned long long ull;

typedef enum {
  ok,
  inv_argc,
  unknown_file,
  unknown_flag,
  mask_not_ok
} st_code;

st_code input(int argc, char* argv[]);

byte xor8(FILE* stream);
byte4 xor32(FILE* steam);

int search_for_mask(FILE* stream, ull* res, const char* mask);

#endif