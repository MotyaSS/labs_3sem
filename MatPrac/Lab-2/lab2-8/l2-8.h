#ifndef L2_8_H
#define L2_8_H

#include <stdlib.h>
#include <stdbool.h>

typedef enum {
  sum_ok,
  sum_base_inv,
  sum_bad_alloc,
  sum_num_inv,
  sum_cnt_inv
} sum_st_code;

bool is_num_valid(const char* str, int base);
const char* skip_leading_zeros(const char* num);
int shift_str_for_i(char* str, unsigned int i);

unsigned char int_to_ascii(int a);
int ascii_to_int(char a);

sum_st_code sum_base_n(size_t cnt, int base, char** res, ...);
sum_st_code sum_up(int base, char** res, size_t* res_size, const char* num);

#endif