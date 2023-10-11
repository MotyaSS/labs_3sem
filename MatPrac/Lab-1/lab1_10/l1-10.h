#ifndef L1_10_H
#define L1_10_H
#include <stdbool.h>

typedef enum {
  OK,
  INCORRECT_STRING,
  INVALID_BASE
} myf_sc;

void get_string_safely_realloc(char** string, int* str_capacity, FILE* stream);
void show_number_with_base(long num, const int base);
myf_sc find_max_from_input(char** string, int* cap, long* result);
int input_numbers(char** string, int* cap, long* max_, const int base);
bool if_lowercase_in_string(const char* string);
#endif