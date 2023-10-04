#include <stdlib.h>
#include <stdio.h>
#include "l1-10.h"

void get_string_safely_realloc(char** string, int* str_capacity, FILE* stream) {
  if (stream == NULL || string == NULL) {
    return;
  }
  int size = 0;
  int a;
  while ((a = getc(stream)) != EOF && a != '\n') {
    (*string)[size++] = (char) a;
    if (size >= *str_capacity) {
      *str_capacity = *str_capacity * 2;
      *string = (char*) realloc(*string, *str_capacity);
      if (string == NULL) {
        perror("PIZDEC VASYAN PRIPLILI\n");
        return;
      }
    }
  }
  (*string)[size] = '\0';
}
