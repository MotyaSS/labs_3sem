#include <stdio.h>
# include <stdlib.h>

char* allocate_and_get_string(FILE* stream) {
  int capacity = BUFSIZ;
  int size = 0;
  char* string = (char*) malloc(capacity);
  int a;
  while ((a = getc(stream)) != EOF && a != '\n') {
    string[size++] = (char) a;
    if (size >= capacity) {
      capacity = capacity * 2;
      realloc(string, capacity);
    }
  }
  string[size] = '\0';
  return string;
}

int main() {
  char* a = allocate_and_get_string(stdin);
  printf("%s\n", a);
  free(a);
}
