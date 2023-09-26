#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include "l1-4.h"
#include "..\my_flag_lib.h"

int flags_handling(const char* flag, int argc, char* argv[], bool if_output) {
  int argc_targ = 3 + (if_output ? 1 : 0);

  if (argc != argc_targ)
    return ARGC_ERROR;

  FILE* input = fopen(argv[2], "r");
  FILE* output = NULL;
  if (if_output)
    output = fopen(argv[3], "w");
  else {
    char out_name[BUFF_SIZE] = "out_";
    strncat(out_name, argv[2], BUFF_SIZE - 4);
    output = fopen(out_name, "w");
  }
  int code;
  switch (*flag) {
    case 'd':
      code = d_fl(input, output);
      break;
    case 'i':
      code = i_fl(input, output);
      break;
    case 's':
      code = s_fl(input, output);
      break;
    case 'a':
      code = a_fl(input, output);
      break;
    default:
      code = FLAG_UNKNOWN;
  }

  fclose(input);
  fclose(output);
  return code;
}

int input(int argc, char* argv[]) {
  if (argc < 2)
    return TOO_FEW_ARGS;
  if (!if_flag(argv[1])) {
    return FLAG_ERROR;
  }
  char flag[BUFF_SIZE];
  if (strlen(argv[1]) >= BUFF_SIZE)
    return FLAG_TOO_LONG;
  strcpy_without_first(argv[1], flag);
  bool if_output = false;
  char* t_fl = flag;
  if (flag[0] == 'n') {
    if_output = true;
    t_fl++;
  }
  return flags_handling(t_fl, argc, argv, if_output);
}

int d_fl(FILE* input, FILE* output) {
  if (input == NULL || output == NULL)
    return FILE_IS_NULL;
  char a = '\0';
  while (!feof(input)) {
    fscanf(input, "%c", &a);
    if (isdigit(a))
      continue;
    fprintf(output, "%c", a);
  }
  return 0;
}

int i_fl(FILE* input, FILE* output) {

}

int s_fl(FILE* input, FILE* output) {

}

int a_fl(FILE* input, FILE* output) {

}