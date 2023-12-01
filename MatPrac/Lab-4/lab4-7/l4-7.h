#ifndef LAB_4_7
#define LAB_4_7

#include "../../Lab-3/lab3-4/my_string.h"
#include <stdio.h>

typedef long long ll;
typedef struct {
  String* buf;
  size_t cap;
  size_t cnt;
} StringVec;

int str_vec_init(StringVec* vec, size_t cap);
int str_vec_resize(StringVec* vec, size_t cap);
int str_vec_add(StringVec* vec, String* to_add);
int str_vec_clear(StringVec* vec);
int str_vec_dest(StringVec* vec);

int string_push_back(String* str, char ch);

typedef enum {
  parse_rv_ok,
  parse_rv_bad_alloc,
  parse_rv_uninit,
  parse_rv_inv
} parse_rv;


typedef struct {
  char* name;
  int value;
} MemoryCell;

int mem_cell_constr(MemoryCell* cell, char* name, int value);
int mem_cell_print(MemoryCell* cell, FILE* out);
int mem_cell_destr(MemoryCell* cell);

typedef struct {
  MemoryCell* arr;
  size_t cap;
  size_t size;
} MemoryVec;

int mem_vec_constr(MemoryVec* vec, int cap);
int mem_vec_destr(MemoryVec* vec);
int mem_vec_print(MemoryVec* vec, FILE* out);
ll find_index_byname(const MemoryVec* vec, char* name);
int mem_vec_resize(MemoryVec* vec, size_t new_size);
int mem_vec_add(MemoryVec* vec, const MemoryCell* cell);

parse_rv parse_expression(StringVec* expression, MemoryVec* mvec, FILE* out);
parse_rv parse_file(FILE* in, FILE* out);
parse_rv parse_string(const String* str, StringVec* expr_vec);
#endif