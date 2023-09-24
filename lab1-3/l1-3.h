
enum {
  TOO_FEW_ARGS = -10,
  FLAG_ERROR,
  FLAG_UNKNOWN,
  FLAG_TOO_LONG
};

int flags_handling(char* flag, int argc, char* argv[]);
int input(int argc, char* argv[]);