#include <stdbool.h>

#define BUFF_SIZE 100

enum {
  TOO_FEW_ARGS = 1,
  FLAG_ERROR,
  FLAG_UNKNOWN,
  FLAG_TOO_LONG,
  ARGC_ERROR,
};
enum {
  FILE_IS_NULL = -1
};

int input(int argc, char* argv[]);
int flags_handling(const char* flag, int argc, char* argv[], bool if_output);

int d_fl(FILE* input, FILE* output);
int i_fl(FILE* input, FILE* output);
int s_fl(FILE* input, FILE* output);
int a_fl(FILE* input, FILE* output);