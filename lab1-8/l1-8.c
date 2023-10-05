#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "l1-8.h"

st_code input(int argc, char* argv[]) {
  if (argc != 3) {
    return INVALID_ARGC;
  }
  FILE* input = fopen(argv[1], "r");
  if (input == NULL) {
    return INVALID_FILE;
  }
  FILE* output = fopen(argv[2], "w");
  st_code code = file_handle(input, output);
  fclose(input);
  fclose(output);
  return code;
}

st_code file_handle(FILE* input, FILE* output) {
  if (input == NULL || output == NULL) {
    return INVALID_FILE;
  }

  do {
    char str[BUFSIZ];
    if (get_str_between_spaces(input, str, BUFSIZ) == STR_OK && is_str_ok_to_convert(str)) {
      int base = find_min_base(str);
      print_num_to_file(str, base, output);
    }
  } while (!feof(input));
  return OK;
}

bool is_str_ok_to_convert(char* str) {
  while (*str != '\0') {
    if (!isalnum(*str)) {
      return false;
    }
    str++;
  }
  return true;
}

int skip_whitespace_and_get_first_token(FILE* stream) { // возвращает первый после пробела символ
  int a;
  while (isspace(a = fgetc(stream)));
  return a;
}

get_str_num_st_code get_str_between_spaces(FILE* stream, char* str, int size) {
  if (stream == NULL) {
    return STREAM_ERR;
  }
  int a = skip_whitespace_and_get_first_token(stream);
  if (a == EOF) {
    str[0] = '\0';
    return STR_OK;
  }
  int cntr = 0;

  str[cntr++] = a;
  while (!isspace(a = fgetc(stream)) && a != EOF) {
    str[cntr++] = a;
    if (cntr >= size) {
      return BUFF_OVERFLOW;
    }
  }
  str[cntr] = '\0';
  return STR_OK;
}

int find_min_base(const char* str) {
  int base = 0;

  for (int i = 0; str[i] != '\0'; i++) {
    if (!isalnum(str[i])) {
      return 0;
    }
    int a = tolower(str[i]);
    a = 1 + (isdigit(a) ? (a - '0') : (a + 10 - 'a'));
    base = a > base ? a : base;
  }
  if (base == 1) { // строка только из нулей == ИНВАЛИД
    return 0;
  }
  return base;
}

int print_num_to_file(char* num, int base, FILE* output) {
  while ((*num) == '0') {
    num++;
  }

  if ((*num) == '\0') {
    return -1;
  }

  char* end = NULL;
  long long result = strtoll(num, &end, base);
  if (end != num + strlen(num)) {
    return -1;
  }
  fprintf(output, "%s, %d, %lld\n", num, base, result);
  return 0;
}