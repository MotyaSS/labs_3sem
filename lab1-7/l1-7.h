#ifndef L1_7_H_
#define L1_7_H_

#include <stdio.h>

typedef enum {
  OK,
  FILE_IS_NULL,
  INVALID_ARGC,
  NOT_FLAG,
  UNKNOWN_FLAG
} st_code;


st_code input(int argc, char* argv[]);
st_code flag_handling(char* flag, int argc, char** argv);

st_code r_fl(int argc, char* argv[]);
st_code r_strange_cat(FILE* input1, FILE* input2, FILE* output);
int put_rest_of_f1_to_f2(FILE* f1, FILE* f2);

int alloc_and_get_lexema(char** str, FILE* stream);

st_code a_fl(int argc, char* argv[]);
st_code a_strange_transform(FILE* input, FILE* output);
int ascii_base_4(char* res, int ch);
#endif