#ifndef L2_2_H
#define L2_2_H

#include <stdio.h>

typedef struct {
  long index;
  long line;
} char_info;

typedef enum {
  find_ok,
  find_eof,
  find_not_ok,
  find_cnt_inv
} find_substr_st;

find_substr_st find_all_substr_in_multiple_files(int count, const char* substr, ...);
int find_substr_in_file(char_info* info, const char* str, FILE* stream, char_info* ptr_pos);
find_substr_st find_all_substr(const char* str, const char* filename, char_info** substr_indexes);

#endif