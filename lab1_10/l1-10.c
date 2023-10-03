#include <stdlib.h>
#include <stdio.h>
#include "l1-10.h"

void get_string_safely_realloc(smart_string* str, FILE* stream) {
  if (stream == NULL || str == NULL) {
    return;
  }
  char** string = &str->str;
  int* sz = &str->len;
  *sz = 0; //начинаем строку с начала переписывать, в этой проге не надо дописывать в уже готовую строку
  int* cap = &str->capacity;
  if (string == NULL || sz == NULL || cap == NULL) {
    return;
  }
  int a;
  while ((a = getc(stream)) != EOF && a != '\n') {
    (*string)[(*sz)++] = (char) a;
    if (*sz >= *cap) {
      *cap = *cap * 2;
      *string = (char*) realloc(*string, *cap);
      if (string == NULL) {
        perror("PIZDEC VASYAN PRIPLILI\n");
        return;
      }
    }
  }
  (*string)[*sz] = '\0';
}
