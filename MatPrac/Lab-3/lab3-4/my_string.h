#ifndef L3_4_STRING
#define L3_4_STRING

#include <stdlib.h>
#include <stdio.h>

typedef struct _string {
  char* _buf;
  size_t _size;
  size_t _cap; // Terminating 0 is excluded
} String;

typedef enum{
  get_str_ok,
  get_str_bad_alloc,
  get_str_empty,
  get_str_eof
} get_str_st;

int string_resize(String* str, size_t n);

int string_init(String* str, size_t n);
int string_constr(char const* src, String* dest);
int string_destr(String* str);

int string_clear(String* str);
void show_string(String const* str);
void str_fprint(String const* str, FILE* stream);
get_str_st get_string(String* str, FILE* stream);

int string_is_equal(String const* str1, String const* str2);
int str_is_equal_charp(String const *str1, char const *str2);
int str1_cmp_str2(String const* str1, String const* str2); // 1 if first greater, -1 if second greater, 0 if equal
int string_copy(String const* src, String* dest);

#endif