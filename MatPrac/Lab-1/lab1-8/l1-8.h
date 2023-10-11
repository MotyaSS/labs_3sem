#ifndef L1_10_H
#define L1_10_H

#include <stdbool.h>
#include <stdio.h>

typedef enum {
  OK,
  INVALID_ARGC,
  INVALID_FILE
} st_code;

typedef enum {
  STR_OK,
  BUFF_OVERFLOW,
  STREAM_ERR
} get_str_num_st_code;

st_code input(int argc, char* argv[]);
st_code file_handle(FILE* input, FILE* output);
get_str_num_st_code get_str_between_spaces(FILE* stream, char* str, int size);
bool is_str_ok_to_convert(char* str);
int skip_whitespace_and_get_first_token(FILE* stream);
int find_min_base(const char* str);
int print_num_to_file(char* num, int base, FILE* output);

#endif