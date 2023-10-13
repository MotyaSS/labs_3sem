#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include "l1-4.h"
#include "../../../my_flag_lib.h"

int make_out_name(char* out_name, char* in_name) {
  size_t len = strlen(in_name);
  for(int i = 0; i < len + 4 + 1; i++){
    out_name[i] = 0;
  }
  char* a = in_name;
  size_t i = 0;
  while (true) {
    if (a[0] != '.' || a[1] != '.' || (a[2] != '/' && a[2] != '\\'))
      break;
    a += 3;
    i += 3;
  }
  strncpy(out_name, in_name, i);
  strncat(out_name, "out_", 4);
  strncat(out_name, a, len + 4 - i);
  return 0;
}

st_code flags_handling(const char* flag, int argc, char* argv[], bool if_output) {
  int argc_targ = 3 + (if_output ? 1 : 0);

  if (argc != argc_targ) {
    return ARGC_ERROR;
  }

  FILE* input = fopen(argv[2], "r");
  FILE* output = NULL;
  if (input == NULL) {
    return FILE_IS_NULL;
  }
  if (if_output) {
    output = fopen(argv[3], "w");
  } else {
    size_t len = strlen(argv[2]);
    char* out_name = (char*) malloc(len + 4 + 1);

    make_out_name(out_name, argv[2]);
    output = fopen(out_name, "w");
    free(out_name);
  }
  int code;
  switch (*flag) {
    case 'd':
      code = digit_exclude(input, output);
      break;
    case 'i':
      code = alpha_count(input, output);
      break;
    case 's':
      code = non_digit_non_space_non_alpha_count(input, output);
      break;
    case 'a':
      code = non_digit_ascii_replace(input, output);
      break;
    default:
      code = FLAG_UNKNOWN;
  }

  fclose(input);
  fclose(output);
  return code;
}

st_code input(int argc, char* argv[]) {
  if (argc < 2) {
    return TOO_FEW_ARGS;
  }
  if (!if_flag(argv[1])) {
    return FLAG_ERROR;
  }
  char flag[BUFF_SIZE];
  if (strlen(argv[1]) >= BUFF_SIZE) {
    return FLAG_TOO_LONG;
  }
  strcpy_without_first(argv[1], flag);
  bool if_output = false;
  char* t_fl = flag;
  if (flag[0] == 'n') {
    if_output = true;
    t_fl++;
  }
  return flags_handling(t_fl, argc, argv, if_output);
}

int digit_exclude(FILE* input, FILE* output) {
  if (input == NULL || output == NULL) {
    return FILE_IS_NULL;
  }
  char a = '\0';
  while (!feof(input)) {
    fscanf(input, "%c", &a);
    if (!isdigit(a)) {
      fputc(a, output);
    }
  }
  return OK;
}

int alpha_count(FILE* input, FILE* output) {
  if (input == NULL || output == NULL) {
    return FILE_IS_NULL;
  }

  while (!feof(input)) {
    char a;
    int cntr = 0;
    while ((a = fgetc(input)) != '\n' && !feof(input)) {
      if (isalpha(a)) {
        cntr++;
      }
    }
    fprintf(output, "%d\n", cntr);
  }
  return OK;
}

int non_digit_non_space_non_alpha_count(FILE* input, FILE* output) {
  if (input == NULL || output == NULL) {
    return FILE_IS_NULL;
  }
  while (!feof(input)) {
    char a;
    int cntr = 0;
    while ((a = fgetc(input)) != '\n' && !feof(input)) {
      if (!isalnum(a) || a != ' ') {
        cntr++;
      }
    }
    fprintf(output, "%d\n", cntr);
  }
  return OK;
}

int non_digit_ascii_replace(FILE* input, FILE* output) {
  if (input == NULL || output == NULL) {
    return FILE_IS_NULL;
  }

  while (!feof(input)) {
    char a;
    while ((a = fgetc(input)) != '\n' && !feof(input)) {
      if (isdigit(a)) {
        fprintf(output, "%c\n", a);
      } else {
        fprintf(output, "%X", a);
      }
    }
    fprintf(output, "\n");
  }
  return OK;
}