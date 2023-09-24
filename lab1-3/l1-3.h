#include <stdbool.h>

enum {
  TOO_FEW_ARGS = 1,
  FLAG_ERROR,
  FLAG_UNKNOWN,
  FLAG_TOO_LONG,
  ARGC_ERROR,
  ARGUMENT_IR
};

int q_fl_print(const int argc, const char* argv[]);
int m_fl_print(const int argc, const char* argv[]);
int t_fl_print(const int argc, const char* argv[]);

int flags_handling(char* flag, int argc, char* argv[]);
int input(int argc, char* argv[]);

bool multiplicity(int first, int second);
int quadratic_eq(double ans[6][3], double first, double second, double third, double eps);
int solve_quadr_eq(int* ans, double a, double b, double c, double eps);

bool triangle(double first, double second, double third, double eps);