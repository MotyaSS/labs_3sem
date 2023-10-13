#ifndef L2_1_H
#define L2_1_H
#define ull unsigned long long

typedef enum {
  ok,
  inv_argc,
  inv_flag,
  unknown_flag,
  inv_num,
  not_enough_space
} st_code;

st_code input(int argc, char* argv[]);

ull str_length(const char* str);
int str_reverse(const char* src, char* dest);
int str_odd_element_toupper(const char* src, char* dest);
int str__num_alph_other__order(const char* src, char* dest);
int cat_string_rand_order(int seed, char* strings_arr[], int str_cnt, char* dest);
#endif