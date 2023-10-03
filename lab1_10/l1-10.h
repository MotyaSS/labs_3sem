#ifndef L1_10_H
#define L1_10_H

typedef struct {
  char* str;
  int capacity;
  int len;
} smart_string;

void get_string_safely_realloc(smart_string* str, FILE* stream);
#endif