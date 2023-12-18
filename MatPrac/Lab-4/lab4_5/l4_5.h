#ifndef L4_5_H
#define L4_5_H

#include "stdio.h"


typedef struct stack_node {
  struct stack_node* next;
  char* value;
} stack_node;

typedef struct {
  stack_node* top;
} stack;

char* stack_pop(stack* st);
char* stack_top(stack* st);
int stack_push(stack* st, char* value);
int stack_destr(stack* st);

typedef enum {
  OK,
  INV_ARGC,
  INV_FILE,
  BAD_ALLOC
} st_code;
int print_st_code(FILE* stream, st_code code);

typedef enum {
  EQ_OK,
  EQ_INV_BRACKET,
  EQ_INV_OP,
  EQ_BAD_ALLOC,
  EQ_UNCOMPUTABLE
} eq_st_code;
int print_eq_err(FILE* stream, const char* expression, eq_st_code code, int cnt);
int print_eq_ok(FILE* stream, const char* expression, char** rev_exp, int value);

st_code execute(int argc, char* argv[]);
st_code compute_file(const char* filepath);
eq_st_code split_expr(const char* src, char*** res);
eq_st_code convert_to_reversed(const char* src, char*** res);
eq_st_code compute_exp(char** rev_exp, long long* result);

#endif