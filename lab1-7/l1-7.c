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


int get_token_or_eof(FILE* f, int* ch) {
  int a;
  while ((a = fgetc(f)) != EOF) {
    if (!isblank(a) && a != '\n') {
      *ch = a;
      return 0;
    }
  }
  *ch = a;
  return -1;
}

int put_rest_of_f1_to_f2(FILE* f1, FILE* f2) {
  char c;
  while (!feof(f1)) {
    get_token_or_eof(f1, &c);
    if (c == EOF) {
      break;
    }
    fprintf(f2, "%c ", c);
  }
  return 0;
}

st_code r_strange_cat(FILE* input1, FILE* input2, FILE* output) {
  if (!input1 || !input2 || !output) {
    return FILE_IS_NULL;
  }
  while (!feof(input1) && !feof(input2)) {
    int c;
    get_token_or_eof(input1, &c);
    if (c == EOF) {
      break;
    }
    fprintf(output, "%c ", c);
    get_token_or_eof(input2, &c);
    if (c == EOF) {
      break;
    }
    fprintf(output, "%c ", c);
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
    remainder = quotient % 4;
    quotient = quotient / 4;

    res[index++] = remainder + '0';
  }

  res[index] = '\0';
  strrev(res);
  return 0;
}

st_code a_strange_cat(FILE* input, FILE* output) {
  if (!input || !output) {
    return FILE_IS_NULL;
  }
  int a;
  size_t count = 0;
  while (!feof(input)) {
    count++;
    get_token_or_eof(input, &a);
    if (a == EOF) {
      break;
    }
    if (count % 10 == 0) {
      char buff[5];
      ascii_base_4(buff, tolower(a));
      fprintf(output, "%s", buff);
    } else if (count % 2 == 0) {
      fprintf(output, "%c", tolower(a));
    } else if (count % 5 == 0) {
      fprintf(output, "%o", a);
    } else {
      fprintf(output, "%c", a);
    }
    fprintf(output, " ");
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
  st_code res = a_strange_cat(input, output);
  fclose(input);
  fclose(output);
  return res;
}