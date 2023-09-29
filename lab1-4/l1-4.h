#include <stdbool.h>

#define BUFF_SIZE 100

typedef enum {
  FILE_IS_NULL = -1,
  OK,
  TOO_FEW_ARGS,
  FLAG_ERROR,
  FLAG_UNKNOWN,
  FLAG_TOO_LONG,
  ARGC_ERROR,
} st_code;

st_code input(int argc, char* argv[]);
st_code flags_handling(const char* flag, int argc, char* argv[], bool if_output);

int digit_exclude(FILE* input, FILE* output);
int alpha_count(FILE* input, FILE* output);
int non_digit_non_space_non_alpha_count(FILE* input, FILE* output);
int non_digit_ascii_replace(FILE* input, FILE* output);