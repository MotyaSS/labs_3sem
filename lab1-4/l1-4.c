#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "l1-4.h"
#include "..\my_flag_lib.h"

int flags_handling(const char* flag, int argc, char* argv[], bool if_output) {
  int argc_targ = 3 + (if_output ? 1 : 0);

  if(argc != argc_targ)
    return ARGC_ERROR;

  FILE* input = fopen(argv[2], "r");
  FILE* output = NULL;
  if(if_output)
    output = fopen(argv[3], "r");
  else {
    size_t size = (strlen(argv[2]) + 4);
    char* out_name = (char*)malloc(sizeof(char) * (size + 1));
    out_name = "out_";
    strncat(out_name, argv[2], size - 4);
    output = fopen(out_name, "w");
    free(out_name);
  }


  switch (*flag) {
    case 'd':
      return d_fl(input, output);
    case 'i':
      return i_fl(input, output);
    case 's':
      return s_fl(input, output);
    case 'a':
      return a_fl(input, output);
    default:
      return FLAG_UNKNOWN;
  }
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
  if(flag[0] == 'n') {
    if_output = true;
    t_fl++;
  }
  return flags_handling(t_fl, argc, argv, if_output);
}
