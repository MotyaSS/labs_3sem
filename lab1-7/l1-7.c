#include "..\my_flag_lib.h"
#include "l1-7.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

st_code input(int argc, char* argv[]) {
  if (argc < 2) {
    return INVALID_ARGC;
  }
  if (!if_flag(argv[1])) {
    return NOT_FLAG;
  }
  char* flag = argv[1];
  flag++;

  st_code code = flag_handling(flag, argc, argv);
  return code;
}

st_code flag_handling(char* flag, int argc, char** argv) {
  if (strlen(flag) != 1) {
    return UNKNOWN_FLAG;
  }
  switch (*flag) {
    case 'a':
      return a_fl(argc, argv);
    case 'r':
      return r_fl(argc, argv);
    default:
      return UNKNOWN_FLAG;
  }
}

#include <stdlib.h>

int alloc_and_get_lexema(char** str, FILE* stream) {
  int a;
  while (isspace(a = fgetc(stream)));
  if (feof(stream)) {
    return -1;
  }
  int count = 0;
  size_t size = 8;
  *str = (char*) malloc(sizeof(char) * size);
  (*str)[count++] = a;
  if (*str == NULL) {
    return -1;
  }
  while (!isspace(a = fgetc(stream)) && a != EOF) {
    (*str)[count++] = a;

    if (count >= size) {
      size *= 2;
      char* new_str = (char*) realloc(*str, sizeof(char) * size);
      if (new_str == NULL) {
        return -1;
      }
      *str = new_str;
    }
  }
  (*str)[count] = 0;
  return 0;
}

int put_rest_of_f1_to_f2(FILE* f1, FILE* f2) {
  char* str = NULL;
  while (alloc_and_get_lexema(&str, f1) != -1) {
    fprintf(f2, "%s ", str);
    free(str);
    str = NULL;
  }
  return 0;
}

st_code r_strange_cat(FILE* input1, FILE* input2, FILE* output) {
  if (!input1 || !input2 || !output) {
    return FILE_IS_NULL;
  }
  while (!feof(input1) && !feof(input2)) {
    char* str = NULL;
    if (alloc_and_get_lexema(&str, input1) != -1) {
      fprintf(output, "%s ", str);
      free(str);
      str = NULL;
    }
    if (alloc_and_get_lexema(&str, input2) != -1) {
      fprintf(output, "%s ", str);
      free(str);
      str = NULL;
    }
  }
  put_rest_of_f1_to_f2(input1, output);
  put_rest_of_f1_to_f2(input2, output);
  return OK;
}

st_code r_fl(int argc, char* argv[]) {
  if (argc != 5) {
    return INVALID_ARGC;
  }
  FILE* input1 = fopen(argv[2], "r");
  if (input1 == NULL) {
    return FILE_IS_NULL;
  }
  FILE* input2 = fopen(argv[3], "r");
  if (input2 == NULL) {
    fclose(input1);
    return FILE_IS_NULL;
  }
  FILE* output = fopen(argv[4], "w");
  if (output == NULL) {
    fclose(input1);
    fclose(input2);
    return FILE_IS_NULL;
  }

  st_code res = r_strange_cat(input1, input2, output);
  fclose(input1);
  fclose(input2);
  fclose(output);
  return res;
}

int ascii_base_4(char* res, int ch) {
  int quotient = ch;
  int remainder;
  int index = 0;

  while (quotient != 0) {
    remainder = quotient & 3;
    quotient = quotient >> 2;

    res[index++] = remainder + '0';
  }

  res[index] = '\0';
  strrev(res);
  return 0;
}

int print_formated_str(size_t count, FILE* output, char* str) {
  if (count % 10 == 0) {
    char buff[5];
    for (int i = 0; str[i] != '\0'; i++) {
      ascii_base_4(buff, tolower(str[i]));
      fprintf(output, "%s|", buff);
    }
  } else if (count % 2 == 0) {
    for (int i = 0; str[i] != '\0'; i++) {
      fprintf(output, "%c", tolower(str[i]));
    }
  } else if (count % 5 == 0) {
    for (int i = 0; str[i] != '\0'; i++) {
      fprintf(output, "%o|", str[i]);
    }
  } else {
    fprintf(output, "%s", str);
  }
  fprintf(output, " ");
  return 0;
}

st_code a_strange_transform(FILE* input, FILE* output) {
  if (!input || !output) {
    return FILE_IS_NULL;
  }
  size_t count = 0;
  while (!feof(input)) {
    count++;
    char* str;
    if (alloc_and_get_lexema(&str, input) != -1) {
      print_formated_str(count, output, str);
      free(str);
    }
  }
  return OK;
}

st_code a_fl(int argc, char* argv[]) {
  if (argc != 4) {
    return INVALID_ARGC;
  }
  FILE* input = fopen(argv[2], "r");
  if (!input) {
    return FILE_IS_NULL;
  }
  FILE* output = fopen(argv[3], "w");
  st_code res = a_strange_transform(input, output);
  fclose(input);
  fclose(output);
  return res;
}